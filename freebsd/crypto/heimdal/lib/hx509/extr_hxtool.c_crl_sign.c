#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct crl_sign_options {char* signer_string; scalar_t__ crl_file_string; scalar_t__ lifetime_string; int /*<<< orphan*/  pass_strings; } ;
typedef  int /*<<< orphan*/  hx509_query ;
typedef  int /*<<< orphan*/  hx509_lock ;
typedef  int /*<<< orphan*/  hx509_crl ;
typedef  int /*<<< orphan*/ * hx509_certs ;
typedef  int /*<<< orphan*/ * hx509_cert ;
struct TYPE_3__ {int /*<<< orphan*/  data; int /*<<< orphan*/  length; } ;
typedef  TYPE_1__ heim_octet_string ;

/* Variables and functions */
 int /*<<< orphan*/  HX509_QUERY_OPTION_PRIVATE_KEY ; 
 int /*<<< orphan*/  context ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hx509_cert_free (int /*<<< orphan*/ *) ; 
 int hx509_certs_append (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int hx509_certs_find (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  hx509_certs_free (int /*<<< orphan*/ **) ; 
 int hx509_certs_init (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  hx509_crl_add_revoked_certs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int hx509_crl_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hx509_crl_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hx509_crl_lifetime (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hx509_crl_sign (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  hx509_err (int /*<<< orphan*/ ,int,int,char*,...) ; 
 int /*<<< orphan*/  hx509_lock_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hx509_lock_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int hx509_query_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  hx509_query_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hx509_query_match_option (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_strings (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int parse_time (scalar_t__,char*) ; 
 int /*<<< orphan*/  rk_dumpdata (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
crl_sign(struct crl_sign_options *opt, int argc, char **argv)
{
    hx509_crl crl;
    heim_octet_string os;
    hx509_cert signer = NULL;
    hx509_lock lock;
    int ret;

    hx509_lock_init(context, &lock);
    lock_strings(lock, &opt->pass_strings);

    ret = hx509_crl_alloc(context, &crl);
    if (ret)
	errx(1, "crl alloc");

    if (opt->signer_string == NULL)
	errx(1, "signer missing");

    {
	hx509_certs certs = NULL;
	hx509_query *q;

	ret = hx509_certs_init(context, opt->signer_string, 0,
			       NULL, &certs);
	if (ret)
	    hx509_err(context, 1, ret,
		      "hx509_certs_init: %s", opt->signer_string);

	ret = hx509_query_alloc(context, &q);
	if (ret)
	    hx509_err(context, 1, ret, "hx509_query_alloc: %d", ret);

	hx509_query_match_option(q, HX509_QUERY_OPTION_PRIVATE_KEY);

	ret = hx509_certs_find(context, certs, q, &signer);
	hx509_query_free(context, q);
	hx509_certs_free(&certs);
	if (ret)
	    hx509_err(context, 1, ret, "no signer certificate found");
    }

    if (opt->lifetime_string) {
	int delta;

	delta = parse_time(opt->lifetime_string, "day");
	if (delta < 0)
	    errx(1, "Invalid lifetime: %s", opt->lifetime_string);

	hx509_crl_lifetime(context, crl, delta);
    }

    {
	hx509_certs revoked = NULL;
	int i;

	ret = hx509_certs_init(context, "MEMORY:revoked-certs", 0,
			       NULL, &revoked);
	if (ret)
	    hx509_err(context, 1, ret,
		      "hx509_certs_init: MEMORY cert");

	for (i = 0; i < argc; i++) {
	    ret = hx509_certs_append(context, revoked, lock, argv[i]);
	    if (ret)
		hx509_err(context, 1, ret, "hx509_certs_append: %s", argv[i]);
	}

	hx509_crl_add_revoked_certs(context, crl, revoked);
	hx509_certs_free(&revoked);
    }

    hx509_crl_sign(context, signer, crl, &os);

    if (opt->crl_file_string)
	rk_dumpdata(opt->crl_file_string, os.data, os.length);

    free(os.data);

    hx509_crl_free(context, &crl);
    hx509_cert_free(signer);
    hx509_lock_free(lock);

    return 0;
}