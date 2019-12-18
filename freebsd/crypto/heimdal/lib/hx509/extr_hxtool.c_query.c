#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct query_options {scalar_t__ print_flag; int /*<<< orphan*/  expr_string; scalar_t__ digitalSignature_flag; scalar_t__ keyEncipherment_flag; scalar_t__ private_key_flag; scalar_t__ eku_string; int /*<<< orphan*/  friendlyname_string; int /*<<< orphan*/  pass_strings; } ;
typedef  int /*<<< orphan*/  hx509_query ;
typedef  int /*<<< orphan*/  hx509_lock ;
typedef  int /*<<< orphan*/  hx509_certs ;
typedef  int /*<<< orphan*/  hx509_cert ;
typedef  int /*<<< orphan*/  heim_oid ;

/* Variables and functions */
 int /*<<< orphan*/  HX509_QUERY_OPTION_KU_DIGITALSIGNATURE ; 
 int /*<<< orphan*/  HX509_QUERY_OPTION_KU_ENCIPHERMENT ; 
 int /*<<< orphan*/  HX509_QUERY_OPTION_PRIVATE_KEY ; 
 int /*<<< orphan*/  context ; 
 int /*<<< orphan*/  der_free_oid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  hx509_cert_free (int /*<<< orphan*/ ) ; 
 int hx509_certs_append (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int hx509_certs_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hx509_certs_free (int /*<<< orphan*/ *) ; 
 int hx509_certs_init (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hx509_err (int /*<<< orphan*/ ,int,int,char*) ; 
 int /*<<< orphan*/  hx509_lock_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hx509_lock_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int hx509_query_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  hx509_query_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int hx509_query_match_eku (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hx509_query_match_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hx509_query_match_friendly_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hx509_query_match_option (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_strings (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_oid (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_certificate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int
query(struct query_options *opt, int argc, char **argv)
{
    hx509_lock lock;
    hx509_query *q;
    hx509_certs certs;
    hx509_cert c;
    int ret;

    ret = hx509_query_alloc(context, &q);
    if (ret)
	errx(1, "hx509_query_alloc: %d", ret);

    hx509_lock_init(context, &lock);
    lock_strings(lock, &opt->pass_strings);

    ret = hx509_certs_init(context, "MEMORY:cert-store", 0, NULL, &certs);
    if (ret) hx509_err(context, 1, ret, "hx509_certs_init: MEMORY");

    while (argc > 0) {

	ret = hx509_certs_append(context, certs, lock, argv[0]);
	if (ret)
	    errx(1, "hx509_certs_append: %s: %d", argv[0], ret);

	argc--;
	argv++;
    }

    if (opt->friendlyname_string)
	hx509_query_match_friendly_name(q, opt->friendlyname_string);

    if (opt->eku_string) {
	heim_oid oid;

	parse_oid(opt->eku_string, NULL, &oid);

	ret = hx509_query_match_eku(q, &oid);
	if (ret)
	    errx(1, "hx509_query_match_eku: %d", ret);
	der_free_oid(&oid);
    }

    if (opt->private_key_flag)
	hx509_query_match_option(q, HX509_QUERY_OPTION_PRIVATE_KEY);

    if (opt->keyEncipherment_flag)
	hx509_query_match_option(q, HX509_QUERY_OPTION_KU_ENCIPHERMENT);

    if (opt->digitalSignature_flag)
	hx509_query_match_option(q, HX509_QUERY_OPTION_KU_DIGITALSIGNATURE);

    if (opt->expr_string)
	hx509_query_match_expr(context, q, opt->expr_string);

    ret = hx509_certs_find(context, certs, q, &c);
    hx509_query_free(context, q);
    if (ret)
	printf("no match found (%d)\n", ret);
    else {
	printf("match found\n");
	if (opt->print_flag)
	    print_certificate(context, c, 0);
    }

    hx509_cert_free(c);
    hx509_certs_free(&certs);

    hx509_lock_free(lock);

    return ret;
}