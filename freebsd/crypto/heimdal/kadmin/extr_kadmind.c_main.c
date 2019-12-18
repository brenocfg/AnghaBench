#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_storage {int dummy; } ;
struct sockaddr {int dummy; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  krb5_socket_t ;
typedef  int /*<<< orphan*/  krb5_log_facility ;
typedef  int /*<<< orphan*/  krb5_keytab ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  __ss ;
struct TYPE_2__ {int num_strings; int /*<<< orphan*/ ** strings; } ;

/* Variables and functions */
 scalar_t__ ENOTSOCK ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  args ; 
 int /*<<< orphan*/  asprintf (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atoi (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_function ; 
 int /*<<< orphan*/  check_library ; 
 int /*<<< orphan*/ * config_file ; 
 int /*<<< orphan*/  context ; 
 scalar_t__ debug_flag ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ getarg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char**,int*) ; 
 int /*<<< orphan*/  hdb_db_dir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdb_kt_ops ; 
 scalar_t__ help_flag ; 
 int htons (int /*<<< orphan*/ ) ; 
 scalar_t__ kadm5_add_passwd_quality_verifier (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kadm5_setup_passwd_quality_check (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kadmind_loop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  keytab_str ; 
 int /*<<< orphan*/  krb5_err (int /*<<< orphan*/ ,int,scalar_t__,char*) ; 
 int /*<<< orphan*/  krb5_free_config_files (char**) ; 
 int krb5_getportbyname (int /*<<< orphan*/ ,char*,char*,int) ; 
 scalar_t__ krb5_init_context (int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_kt_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_kt_resolve (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_openlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ **) ; 
 scalar_t__ krb5_prepend_config_files_default (int /*<<< orphan*/ *,char***) ; 
 scalar_t__ krb5_set_config_files (int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  krb5_set_default_realm (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ krb5_set_warn_dest (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mini_inetd (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  num_args ; 
 int /*<<< orphan*/  pidfile (int /*<<< orphan*/ *) ; 
 TYPE_1__ policy_libraries ; 
 int /*<<< orphan*/ * port_str ; 
 int /*<<< orphan*/  print_version (int /*<<< orphan*/ *) ; 
 scalar_t__ realm ; 
 int /*<<< orphan*/  rk_INVALID_SOCKET ; 
 scalar_t__ rk_SOCK_ERRNO ; 
 scalar_t__ roken_getsockname (int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  setprogname (char*) ; 
 int /*<<< orphan*/  start_server (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usage (int) ; 
 scalar_t__ version_flag ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

int
main(int argc, char **argv)
{
    krb5_error_code ret;
    char **files;
    int optidx = 0;
    int i;
    krb5_log_facility *logfacility;
    krb5_keytab keytab;
    krb5_socket_t sfd = rk_INVALID_SOCKET;

    setprogname(argv[0]);

    ret = krb5_init_context(&context);
    if (ret)
	errx (1, "krb5_init_context failed: %d", ret);

    if (getarg(args, num_args, argc, argv, &optidx)) {
	warnx("error at argument `%s'", argv[optidx]);
	usage(1);
    }

    if (help_flag)
	usage (0);

    if (version_flag) {
	print_version(NULL);
	exit(0);
    }

    argc -= optidx;
    argv += optidx;

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

    ret = krb5_openlog(context, "kadmind", &logfacility);
    if (ret)
	krb5_err(context, 1, ret, "krb5_openlog");
    ret = krb5_set_warn_dest(context, logfacility);
    if (ret)
	krb5_err(context, 1, ret, "krb5_set_warn_dest");

    ret = krb5_kt_register(context, &hdb_kt_ops);
    if(ret)
	krb5_err(context, 1, ret, "krb5_kt_register");

    ret = krb5_kt_resolve(context, keytab_str, &keytab);
    if(ret)
	krb5_err(context, 1, ret, "krb5_kt_resolve");

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

    if(debug_flag) {
	int debug_port;

	if(port_str == NULL)
	    debug_port = krb5_getportbyname (context, "kerberos-adm",
					     "tcp", 749);
	else
	    debug_port = htons(atoi(port_str));
	mini_inetd(debug_port, &sfd);
    } else {
#ifdef _WIN32
	pidfile(NULL);
	start_server(context, port_str);
#else
	struct sockaddr_storage __ss;
	struct sockaddr *sa = (struct sockaddr *)&__ss;
	socklen_t sa_size = sizeof(__ss);

	/*
	 * Check if we are running inside inetd or not, if not, start
	 * our own server.
	 */

	if(roken_getsockname(STDIN_FILENO, sa, &sa_size) < 0 &&
	   rk_SOCK_ERRNO == ENOTSOCK) {
	    pidfile(NULL);
	    start_server(context, port_str);
	}
#endif /* _WIN32 */
	sfd = STDIN_FILENO;
    }

    if(realm)
	krb5_set_default_realm(context, realm); /* XXX */

    kadmind_loop(context, keytab, sfd);

    return 0;
}