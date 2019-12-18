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
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  heim_sipc ;

/* Variables and functions */
 int /*<<< orphan*/  args ; 
 int /*<<< orphan*/  config ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ getarg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char**,int*) ; 
 int /*<<< orphan*/  heim_ipc_main () ; 
 int /*<<< orphan*/  heim_sipc_launchd_mach_init (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heim_sipc_service_unix (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heim_sipc_timeout (int) ; 
 scalar_t__ help_flag ; 
 int /*<<< orphan*/  kdc_openlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_err (int /*<<< orphan*/ ,int,int,char*) ; 
 int /*<<< orphan*/  krb5_errx (int /*<<< orphan*/ ,int,char*) ; 
 int krb5_init_context (int /*<<< orphan*/ *) ; 
 int krb5_kdc_get_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int krb5_kdc_set_dbinfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntlm_service ; 
 int /*<<< orphan*/  num_args ; 
 int /*<<< orphan*/  print_version (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setprogname (char*) ; 
 int /*<<< orphan*/  usage (int) ; 
 scalar_t__ version_flag ; 

int
main(int argc, char **argv)
{
    krb5_context context;
    int ret, optidx = 0;

    setprogname(argv[0]);

    if (getarg(args, num_args, argc, argv, &optidx))
	usage(1);

    if (help_flag)
	usage(0);

    if (version_flag) {
	print_version(NULL);
	exit(0);
    }

    ret = krb5_init_context(&context);
    if (ret)
	krb5_errx(context, 1, "krb5_init_context");

    ret = krb5_kdc_get_config(context, &config);
    if (ret)
	krb5_err(context, 1, ret, "krb5_kdc_default_config");

    kdc_openlog(context, "digest-service", config);

    ret = krb5_kdc_set_dbinfo(context, config);
    if (ret)
	krb5_err(context, 1, ret, "krb5_kdc_set_dbinfo");

#if __APPLE__
    {
	heim_sipc mach;
	heim_sipc_launchd_mach_init("org.h5l.ntlm-service",
				    ntlm_service, context, &mach);
	heim_sipc_timeout(60);
    }
#endif
    {
	heim_sipc un;
	heim_sipc_service_unix("org.h5l.ntlm-service", ntlm_service, NULL, &un);
    }

    heim_ipc_main();
    return 0;
}