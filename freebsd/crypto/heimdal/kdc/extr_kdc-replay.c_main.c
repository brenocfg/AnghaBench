#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;
struct sockaddr_storage {int dummy; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  sa ;
typedef  int /*<<< orphan*/  krb5_storage ;
typedef  int krb5_socklen_t ;
struct TYPE_11__ {int /*<<< orphan*/  pkinit_kdc_revoke; int /*<<< orphan*/  pkinit_kdc_cert_pool; int /*<<< orphan*/ * pkinit_kdc_anchors; int /*<<< orphan*/ * pkinit_kdc_identity; scalar_t__ enable_pkinit; } ;
typedef  TYPE_1__ krb5_kdc_configuration ;
typedef  scalar_t__ krb5_error_code ;
struct TYPE_12__ {scalar_t__ length; int /*<<< orphan*/ * data; } ;
typedef  TYPE_2__ krb5_data ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  krb5_address ;
typedef  int /*<<< orphan*/  astr ;
typedef  int /*<<< orphan*/  Der_type ;
typedef  int /*<<< orphan*/  Der_class ;

/* Variables and functions */
 scalar_t__ HEIM_ERR_EOF ; 
 scalar_t__ KRB5_PROG_ATYPE_NOSUPP ; 
 int MAKE_TAG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  args ; 
 scalar_t__ der_get_tag (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  err (int,char*,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ getarg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char**,int*) ; 
 scalar_t__ help_flag ; 
 int /*<<< orphan*/  kdc_openlog (int /*<<< orphan*/ ,char*,TYPE_1__*) ; 
 scalar_t__ krb5_addr2sockaddr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct sockaddr*,int*,int) ; 
 int /*<<< orphan*/  krb5_data_free (TYPE_2__*) ; 
 int /*<<< orphan*/  krb5_err (int /*<<< orphan*/ ,int,scalar_t__,char*) ; 
 int /*<<< orphan*/  krb5_errx (int /*<<< orphan*/ ,int,char*,...) ; 
 int /*<<< orphan*/  krb5_free_address (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_free_context (int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_init_context (int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_kdc_get_config (int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  krb5_kdc_pk_initialize (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_kdc_process_request (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,scalar_t__,TYPE_2__*,int /*<<< orphan*/ *,char*,struct sockaddr*,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_kdc_set_dbinfo (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  krb5_kdc_update_time (struct timeval*) ; 
 scalar_t__ krb5_print_address (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_ret_address (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_ret_data (int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ krb5_ret_uint32 (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  krb5_set_real_time (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_storage_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * krb5_storage_from_fd (int) ; 
 int /*<<< orphan*/  num_args ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_version (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  setprogname (char*) ; 
 int /*<<< orphan*/  usage (int) ; 
 scalar_t__ version_flag ; 

int
main(int argc, char **argv)
{
    krb5_error_code ret;
    krb5_context context;
    krb5_kdc_configuration *config;
    krb5_storage *sp;
    int fd, optidx = 0;

    setprogname(argv[0]);

    if(getarg(args, num_args, argc, argv, &optidx))
	usage(1);

    if(help_flag)
	usage(0);

    if(version_flag){
	print_version(NULL);
	exit(0);
    }

    ret = krb5_init_context(&context);
    if (ret)
	errx (1, "krb5_init_context failed to parse configuration file");

    ret = krb5_kdc_get_config(context, &config);
    if (ret)
	krb5_err(context, 1, ret, "krb5_kdc_default_config");

    kdc_openlog(context, "kdc-replay", config);

    ret = krb5_kdc_set_dbinfo(context, config);
    if (ret)
	krb5_err(context, 1, ret, "krb5_kdc_set_dbinfo");

#ifdef PKINIT
    if (config->enable_pkinit) {
	if (config->pkinit_kdc_identity == NULL)
	    krb5_errx(context, 1, "pkinit enabled but no identity");

	if (config->pkinit_kdc_anchors == NULL)
	    krb5_errx(context, 1, "pkinit enabled but no X509 anchors");

	krb5_kdc_pk_initialize(context, config,
			       config->pkinit_kdc_identity,
			       config->pkinit_kdc_anchors,
			       config->pkinit_kdc_cert_pool,
			       config->pkinit_kdc_revoke);

    }
#endif /* PKINIT */

    if (argc != 2)
	errx(1, "argc != 2");

    printf("kdc replay\n");

    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
	err(1, "open: %s", argv[1]);

    sp = krb5_storage_from_fd(fd);
    if (sp == NULL)
	krb5_errx(context, 1, "krb5_storage_from_fd");

    while(1) {
	struct sockaddr_storage sa;
	krb5_socklen_t salen = sizeof(sa);
	struct timeval tv;
	krb5_address a;
	krb5_data d, r;
	uint32_t t, clty, tag;
	char astr[80];

	ret = krb5_ret_uint32(sp, &t);
	if (ret == HEIM_ERR_EOF)
	    break;
	else if (ret)
	    krb5_errx(context, 1, "krb5_ret_uint32(version)");
	if (t != 1)
	    krb5_errx(context, 1, "version not 1");
	ret = krb5_ret_uint32(sp, &t);
	if (ret)
	    krb5_errx(context, 1, "krb5_ret_uint32(time)");
	ret = krb5_ret_address(sp, &a);
	if (ret)
	    krb5_errx(context, 1, "krb5_ret_address");
	ret = krb5_ret_data(sp, &d);
	if (ret)
	    krb5_errx(context, 1, "krb5_ret_data");
	ret = krb5_ret_uint32(sp, &clty);
	if (ret)
	    krb5_errx(context, 1, "krb5_ret_uint32(class|type)");
	ret = krb5_ret_uint32(sp, &tag);
	if (ret)
	    krb5_errx(context, 1, "krb5_ret_uint32(tag)");


	ret = krb5_addr2sockaddr (context, &a, (struct sockaddr *)&sa,
				  &salen, 88);
	if (ret == KRB5_PROG_ATYPE_NOSUPP)
	    goto out;
	else if (ret)
	    krb5_err(context, 1, ret, "krb5_addr2sockaddr");

	ret = krb5_print_address(&a, astr, sizeof(astr), NULL);
	if (ret)
	    krb5_err(context, 1, ret, "krb5_print_address");

	printf("processing request from %s, %lu bytes\n",
	       astr, (unsigned long)d.length);

	r.length = 0;
	r.data = NULL;

	tv.tv_sec = t;
	tv.tv_usec = 0;

	krb5_kdc_update_time(&tv);
	krb5_set_real_time(context, tv.tv_sec, 0);

	ret = krb5_kdc_process_request(context, config, d.data, d.length,
				       &r, NULL, astr,
				       (struct sockaddr *)&sa, 0);
	if (ret)
	    krb5_err(context, 1, ret, "krb5_kdc_process_request");

	if (r.length) {
	    Der_class cl;
	    Der_type ty;
	    unsigned int tag2;
	    ret = der_get_tag (r.data, r.length,
			       &cl, &ty, &tag2, NULL);
	    if (MAKE_TAG(cl, ty, 0) != clty)
		krb5_errx(context, 1, "class|type mismatch: %d != %d",
			  (int)MAKE_TAG(cl, ty, 0), (int)clty);
	    if (tag != tag2)
		krb5_errx(context, 1, "tag mismatch");

	    krb5_data_free(&r);
	} else {
	    if (clty != 0xffffffff)
		krb5_errx(context, 1, "clty not invalid");
	    if (tag != 0xffffffff)
		krb5_errx(context, 1, "tag not invalid");
	}

    out:
	krb5_data_free(&d);
	krb5_free_address(context, &a);
    }

    krb5_storage_free(sp);
    krb5_free_context(context);

    printf("done\n");

    return 0;
}