#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sigaction {int /*<<< orphan*/  sa_mask; int /*<<< orphan*/  sa_handler; scalar_t__ sa_flags; } ;
struct servent {int s_port; } ;
typedef  int /*<<< orphan*/  krb5_keytab ;
typedef  scalar_t__ krb5_error_code ;
struct TYPE_7__ {scalar_t__ len; } ;
struct TYPE_6__ {int num_strings; int /*<<< orphan*/ * strings; } ;
struct TYPE_5__ {int num_strings; int /*<<< orphan*/ ** strings; } ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  KPASSWD_PORT ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int TRUE ; 
 int /*<<< orphan*/  add_one_address (int /*<<< orphan*/ ,int) ; 
 TYPE_2__ addresses_str ; 
 int /*<<< orphan*/  args ; 
 int /*<<< orphan*/  asprintf (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_function ; 
 int /*<<< orphan*/  check_library ; 
 int /*<<< orphan*/ * config_file ; 
 int /*<<< orphan*/  context ; 
 int doit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 TYPE_3__ explicit_addresses ; 
 int /*<<< orphan*/  free_getarg_strings (TYPE_2__*) ; 
 int /*<<< orphan*/  hdb_db_dir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdb_kt_ops ; 
 scalar_t__ help_flag ; 
 int htons (int) ; 
 scalar_t__ kadm5_add_passwd_quality_verifier (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kadm5_setup_passwd_quality_check (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  keytab_str ; 
 char** krb5_config_get_strings (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_err (int /*<<< orphan*/ ,int,scalar_t__,char*,...) ; 
 int /*<<< orphan*/  krb5_errx (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  krb5_free_config_files (char**) ; 
 int krb5_getportbyname (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_kt_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_kt_resolve (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_openlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_prepend_config_files_default (int /*<<< orphan*/ *,char***) ; 
 int /*<<< orphan*/  krb5_program_setup (int /*<<< orphan*/ *,int,char**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_set_config_files (int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  krb5_set_default_realm (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  krb5_set_warn_dest (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_std_usage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_facility ; 
 int /*<<< orphan*/  num_args ; 
 int /*<<< orphan*/  pidfile (int /*<<< orphan*/ *) ; 
 TYPE_1__ policy_libraries ; 
 char* port_str ; 
 int /*<<< orphan*/  print_version (int /*<<< orphan*/ *) ; 
 scalar_t__ realm_str ; 
 struct servent* roken_getservbyname (char*,char*) ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigterm ; 
 int strtol (char*,char**,int) ; 
 scalar_t__ version_flag ; 

int
main (int argc, char **argv)
{
    krb5_keytab keytab;
    krb5_error_code ret;
    char **files;
    int port, i;

    krb5_program_setup(&context, argc, argv, args, num_args, NULL);

    if(help_flag)
	krb5_std_usage(0, args, num_args);
    if(version_flag) {
	print_version(NULL);
	exit(0);
    }

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
    if (ret)
	krb5_err(context, 1, ret, "reading configuration files");

    if(realm_str)
	krb5_set_default_realm(context, realm_str);

    krb5_openlog (context, "kpasswdd", &log_facility);
    krb5_set_warn_dest(context, log_facility);

    if (port_str != NULL) {
	struct servent *s = roken_getservbyname (port_str, "udp");

	if (s != NULL)
	    port = s->s_port;
	else {
	    char *ptr;

	    port = strtol (port_str, &ptr, 10);
	    if (port == 0 && ptr == port_str)
		krb5_errx (context, 1, "bad port `%s'", port_str);
	    port = htons(port);
	}
    } else
	port = krb5_getportbyname (context, "kpasswd", "udp", KPASSWD_PORT);

    ret = krb5_kt_register(context, &hdb_kt_ops);
    if(ret)
	krb5_err(context, 1, ret, "krb5_kt_register");

    ret = krb5_kt_resolve(context, keytab_str, &keytab);
    if(ret)
	krb5_err(context, 1, ret, "%s", keytab_str);

    kadm5_setup_passwd_quality_check (context, check_library, check_function);

    for (i = 0; i < policy_libraries.num_strings; i++) {
	ret = kadm5_add_passwd_quality_verifier(context,
						policy_libraries.strings[i]);
	if (ret)
	    krb5_err(context, 1, ret, "kadm5_add_passwd_quality_verifier");
    }
    ret = kadm5_add_passwd_quality_verifier(context, NULL);
    if (ret)
	krb5_err(context, 1, ret, "kadm5_add_passwd_quality_verifier");


    explicit_addresses.len = 0;

    if (addresses_str.num_strings) {
	int j;

	for (j = 0; j < addresses_str.num_strings; ++j)
	    add_one_address (addresses_str.strings[j], j == 0);
	free_getarg_strings (&addresses_str);
    } else {
	char **foo = krb5_config_get_strings (context, NULL,
					      "kdc", "addresses", NULL);

	if (foo != NULL) {
	    add_one_address (*foo++, TRUE);
	    while (*foo)
		add_one_address (*foo++, FALSE);
	}
    }

#ifdef HAVE_SIGACTION
    {
	struct sigaction sa;

	sa.sa_flags = 0;
	sa.sa_handler = sigterm;
	sigemptyset(&sa.sa_mask);

	sigaction(SIGINT,  &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);
    }
#else
    signal(SIGINT,  sigterm);
    signal(SIGTERM, sigterm);
#endif

    pidfile(NULL);

    return doit (keytab, port);
}