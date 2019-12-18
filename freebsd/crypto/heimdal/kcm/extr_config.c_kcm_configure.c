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
typedef  scalar_t__ krb5_error_code ;

/* Variables and functions */
 int /*<<< orphan*/  DETACH_IS_DEFAULT ; 
 int /*<<< orphan*/ * _PATH_KCM_CONF ; 
 int /*<<< orphan*/  args ; 
 scalar_t__ ccache_init_system () ; 
 int /*<<< orphan*/ * config_file ; 
 int detach_from_console ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ getarg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char**,int*) ; 
 scalar_t__ help_flag ; 
 int /*<<< orphan*/  kcm_context ; 
 int /*<<< orphan*/  kcm_openlog () ; 
 int /*<<< orphan*/ * kcm_system_config_get_string (char*) ; 
 int krb5_config_get_bool_default (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *) ; 
 char* krb5_config_get_string (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_err (int /*<<< orphan*/ ,int,scalar_t__,char*) ; 
 int /*<<< orphan*/  krb5_free_config_files (char**) ; 
 scalar_t__ krb5_prepend_config_files_default (int /*<<< orphan*/ *,char***) ; 
 scalar_t__ krb5_set_config_files (int /*<<< orphan*/ ,char**) ; 
 int max_request ; 
 char const* max_request_str ; 
 int /*<<< orphan*/  num_args ; 
 int parse_bytes (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_version (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * system_principal ; 
 int /*<<< orphan*/  usage (int) ; 
 scalar_t__ version_flag ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

void
kcm_configure(int argc, char **argv)
{
    krb5_error_code ret;
    int optind = 0;
    const char *p;

    while(getarg(args, num_args, argc, argv, &optind))
	warnx("error at argument `%s'", argv[optind]);

    if(help_flag)
	usage (0);

    if (version_flag) {
	print_version(NULL);
	exit(0);
    }

    argc -= optind;
    argv += optind;

    if (argc != 0)
	usage(1);

    {
	char **files;

	if(config_file == NULL)
	    config_file = _PATH_KCM_CONF;

	ret = krb5_prepend_config_files_default(config_file, &files);
	if (ret)
	    krb5_err(kcm_context, 1, ret, "getting configuration files");

	ret = krb5_set_config_files(kcm_context, files);
	krb5_free_config_files(files);
	if(ret)
	    krb5_err(kcm_context, 1, ret, "reading configuration files");
    }

    if(max_request_str)
	max_request = parse_bytes(max_request_str, NULL);

    if(max_request == 0){
	p = krb5_config_get_string (kcm_context,
				    NULL,
				    "kcm",
				    "max-request",
				    NULL);
	if(p)
	    max_request = parse_bytes(p, NULL);
    }

    if (system_principal == NULL) {
	system_principal = kcm_system_config_get_string("principal");
    }

    if (system_principal != NULL) {
	ret = ccache_init_system();
	if (ret)
	    krb5_err(kcm_context, 1, ret, "initializing system ccache");
    }

#ifdef SUPPORT_DETACH
    if(detach_from_console == -1)
	detach_from_console = krb5_config_get_bool_default(kcm_context, NULL,
							   DETACH_IS_DEFAULT,
							   "kcm",
							   "detach", NULL);
#endif
    kcm_openlog();
    if(max_request == 0)
	max_request = 64 * 1024;
}