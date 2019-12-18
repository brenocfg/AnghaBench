#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int require_preauth; } ;
typedef  TYPE_1__ krb5_kdc_configuration ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_12__ {scalar_t__ len; } ;
struct TYPE_11__ {int num_strings; int /*<<< orphan*/ * strings; } ;

/* Variables and functions */
 int DETACH_IS_DEFAULT ; 
 int /*<<< orphan*/  ETYPE_DES_CBC_CRC ; 
 int /*<<< orphan*/  ETYPE_DES_CBC_MD4 ; 
 int /*<<< orphan*/  ETYPE_DES_CBC_MD5 ; 
 int /*<<< orphan*/  ETYPE_DES_CBC_NONE ; 
 int /*<<< orphan*/  ETYPE_DES_CFB64_NONE ; 
 int /*<<< orphan*/  ETYPE_DES_PCBC_NONE ; 
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  add_one_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_6__ addresses_str ; 
 int /*<<< orphan*/  args ; 
 int /*<<< orphan*/  asprintf (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ builtin_hdb_flag ; 
 int /*<<< orphan*/ * config_file ; 
 int detach_from_console ; 
 int disable_des ; 
 int enable_http ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 TYPE_7__ explicit_addresses ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  free_getarg_strings (TYPE_6__*) ; 
 scalar_t__ getarg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char**,int*) ; 
 int /*<<< orphan*/  hdb_db_dir (int /*<<< orphan*/ ) ; 
 scalar_t__ hdb_list_builtin (int /*<<< orphan*/ ,char**) ; 
 scalar_t__ help_flag ; 
 int /*<<< orphan*/  kdc_openlog (int /*<<< orphan*/ ,char*,TYPE_1__*) ; 
 int krb5_config_get_bool (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *) ; 
 int krb5_config_get_bool_default (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*,char*,int /*<<< orphan*/ *) ; 
 void* krb5_config_get_string (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *) ; 
 char** krb5_config_get_strings (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_enctype_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_err (int /*<<< orphan*/ ,int,scalar_t__,char*) ; 
 int /*<<< orphan*/  krb5_errx (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  krb5_free_config_files (char**) ; 
 scalar_t__ krb5_kdc_get_config (int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  krb5_kdc_pkinit_config (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ krb5_kdc_set_dbinfo (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  krb5_kdc_windc_init (int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_prepend_config_files_default (int /*<<< orphan*/ *,char***) ; 
 scalar_t__ krb5_set_config_files (int /*<<< orphan*/ ,char**) ; 
 char const* max_request_str ; 
 int max_request_tcp ; 
 int max_request_udp ; 
 int /*<<< orphan*/  num_args ; 
 int parse_bytes (char const*,int /*<<< orphan*/ *) ; 
 char* port_str ; 
 int /*<<< orphan*/  print_version (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/ * request_log ; 
 int require_preauth ; 
 char* strdup (char const*) ; 
 int /*<<< orphan*/  usage (int) ; 
 scalar_t__ version_flag ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

krb5_kdc_configuration *
configure(krb5_context context, int argc, char **argv)
{
    krb5_kdc_configuration *config;
    krb5_error_code ret;
    int optidx = 0;
    const char *p;

    while(getarg(args, num_args, argc, argv, &optidx))
	warnx("error at argument `%s'", argv[optidx]);

    if(help_flag)
	usage (0);

    if (version_flag) {
	print_version(NULL);
	exit(0);
    }

    if (builtin_hdb_flag) {
	char *list;
	ret = hdb_list_builtin(context, &list);
	if (ret)
	    krb5_err(context, 1, ret, "listing builtin hdb backends");
	printf("builtin hdb backends: %s\n", list);
	free(list);
	exit(0);
    }

    argc -= optidx;
    argv += optidx;

    if (argc != 0)
	usage(1);

    {
	char **files;

	if (config_file == NULL) {
	    asprintf(&config_file, "%s/kdc.conf", hdb_db_dir(context));
	    if (config_file == NULL)
		errx(1, "out of memory");
	}

	ret = krb5_prepend_config_files_default(config_file, &files);
	if (ret)
	    krb5_err(context, 1, ret, "getting configuration files");

	ret = krb5_set_config_files(context, files);
	krb5_free_config_files(files);
	if(ret)
	    krb5_err(context, 1, ret, "reading configuration files");
    }

    ret = krb5_kdc_get_config(context, &config);
    if (ret)
	krb5_err(context, 1, ret, "krb5_kdc_default_config");

    kdc_openlog(context, "kdc", config);

    ret = krb5_kdc_set_dbinfo(context, config);
    if (ret)
	krb5_err(context, 1, ret, "krb5_kdc_set_dbinfo");

    if(max_request_str)
	max_request_tcp = max_request_udp = parse_bytes(max_request_str, NULL);

    if(max_request_tcp == 0){
	p = krb5_config_get_string (context,
				    NULL,
				    "kdc",
				    "max-request",
				    NULL);
	if(p)
	    max_request_tcp = max_request_udp = parse_bytes(p, NULL);
    }

    if(require_preauth != -1)
	config->require_preauth = require_preauth;

    if(port_str == NULL){
	p = krb5_config_get_string(context, NULL, "kdc", "ports", NULL);
	if (p != NULL)
	    port_str = strdup(p);
    }

    explicit_addresses.len = 0;

    if (addresses_str.num_strings) {
	int i;

	for (i = 0; i < addresses_str.num_strings; ++i)
	    add_one_address (context, addresses_str.strings[i], i == 0);
	free_getarg_strings (&addresses_str);
    } else {
	char **foo = krb5_config_get_strings (context, NULL,
					      "kdc", "addresses", NULL);

	if (foo != NULL) {
	    add_one_address (context, *foo++, TRUE);
	    while (*foo)
		add_one_address (context, *foo++, FALSE);
	}
    }

    if(enable_http == -1)
	enable_http = krb5_config_get_bool(context, NULL, "kdc",
					   "enable-http", NULL);

    if(request_log == NULL)
	request_log = krb5_config_get_string(context, NULL,
					     "kdc",
					     "kdc-request-log",
					     NULL);

    if (krb5_config_get_string(context, NULL, "kdc",
			       "enforce-transited-policy", NULL))
	krb5_errx(context, 1, "enforce-transited-policy deprecated, "
		  "use [kdc]transited-policy instead");

#ifdef SUPPORT_DETACH
    if(detach_from_console == -1)
	detach_from_console = krb5_config_get_bool_default(context, NULL,
							   DETACH_IS_DEFAULT,
							   "kdc",
							   "detach", NULL);
#endif /* SUPPORT_DETACH */

    if(max_request_tcp == 0)
	max_request_tcp = 64 * 1024;
    if(max_request_udp == 0)
	max_request_udp = 64 * 1024;

    if (port_str == NULL)
	port_str = "+";

    if(disable_des == -1)
	disable_des = krb5_config_get_bool_default(context, NULL,
						   FALSE,
						   "kdc",
						   "disable-des", NULL);
    if(disable_des) {
	krb5_enctype_disable(context, ETYPE_DES_CBC_CRC);
	krb5_enctype_disable(context, ETYPE_DES_CBC_MD4);
	krb5_enctype_disable(context, ETYPE_DES_CBC_MD5);
	krb5_enctype_disable(context, ETYPE_DES_CBC_NONE);
	krb5_enctype_disable(context, ETYPE_DES_CFB64_NONE);
	krb5_enctype_disable(context, ETYPE_DES_PCBC_NONE);
    }

    krb5_kdc_windc_init(context);

    krb5_kdc_pkinit_config(context, config);

    return config;
}