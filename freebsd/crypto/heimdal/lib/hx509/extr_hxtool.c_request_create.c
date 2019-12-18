#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int num_strings; int /*<<< orphan*/ * strings; } ;
struct TYPE_6__ {int num_strings; int /*<<< orphan*/ * strings; } ;
struct request_create_options {TYPE_2__ dnsname_strings; TYPE_1__ email_strings; scalar_t__ verbose_flag; scalar_t__ subject_string; int /*<<< orphan*/  key_bits_integer; int /*<<< orphan*/  generate_key_string; int /*<<< orphan*/  key_string; } ;
typedef  int /*<<< orphan*/  key ;
typedef  int /*<<< orphan*/  hx509_request ;
typedef  int /*<<< orphan*/  hx509_private_key ;
typedef  int /*<<< orphan*/ * hx509_name ;
struct TYPE_8__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
typedef  TYPE_3__ heim_octet_string ;
typedef  int /*<<< orphan*/  SubjectPublicKeyInfo ;

/* Variables and functions */
 int _hx509_request_add_dns_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int _hx509_request_add_email (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int _hx509_request_to_pkcs10 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  context ; 
 int /*<<< orphan*/  der_free_octet_string (TYPE_3__*) ; 
 int /*<<< orphan*/  errx (int,char*,int) ; 
 int /*<<< orphan*/  free_SubjectPublicKeyInfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hx509_err (int /*<<< orphan*/ ,int,int,char*) ; 
 int /*<<< orphan*/  hx509_name_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  hx509_name_to_string (int /*<<< orphan*/ *,char**) ; 
 int hx509_parse_name (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ **) ; 
 int hx509_private_key2SPKI (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hx509_private_key_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hx509_request_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hx509_request_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int hx509_request_set_SubjectPublicKeyInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hx509_request_set_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  rk_dumpdata (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
request_create(struct request_create_options *opt, int argc, char **argv)
{
    heim_octet_string request;
    hx509_request req;
    int ret, i;
    hx509_private_key signer;
    SubjectPublicKeyInfo key;
    const char *outfile = argv[0];

    memset(&key, 0, sizeof(key));

    get_key(opt->key_string,
	    opt->generate_key_string,
	    opt->key_bits_integer,
	    &signer);

    hx509_request_init(context, &req);

    if (opt->subject_string) {
	hx509_name name = NULL;

	ret = hx509_parse_name(context, opt->subject_string, &name);
	if (ret)
	    errx(1, "hx509_parse_name: %d\n", ret);
	hx509_request_set_name(context, req, name);

	if (opt->verbose_flag) {
	    char *s;
	    hx509_name_to_string(name, &s);
	    printf("%s\n", s);
	}
	hx509_name_free(&name);
    }

    for (i = 0; i < opt->email_strings.num_strings; i++) {
	ret = _hx509_request_add_email(context, req,
				       opt->email_strings.strings[i]);
	if (ret)
	    hx509_err(context, 1, ret, "hx509_request_add_email");
    }

    for (i = 0; i < opt->dnsname_strings.num_strings; i++) {
	ret = _hx509_request_add_dns_name(context, req,
					  opt->dnsname_strings.strings[i]);
	if (ret)
	    hx509_err(context, 1, ret, "hx509_request_add_dns_name");
    }


    ret = hx509_private_key2SPKI(context, signer, &key);
    if (ret)
	errx(1, "hx509_private_key2SPKI: %d\n", ret);

    ret = hx509_request_set_SubjectPublicKeyInfo(context,
						  req,
						  &key);
    free_SubjectPublicKeyInfo(&key);
    if (ret)
	hx509_err(context, 1, ret, "hx509_request_set_SubjectPublicKeyInfo");

    ret = _hx509_request_to_pkcs10(context,
				   req,
				   signer,
				   &request);
    if (ret)
	hx509_err(context, 1, ret, "_hx509_request_to_pkcs10");

    hx509_private_key_free(&signer);
    hx509_request_free(&req);

    if (ret == 0)
	rk_dumpdata(outfile, request.data, request.length);
    der_free_octet_string(&request);

    return 0;
}