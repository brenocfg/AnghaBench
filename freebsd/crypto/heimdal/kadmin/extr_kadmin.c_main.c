#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int krb5_error_code ;
struct TYPE_8__ {int /*<<< orphan*/  mask; scalar_t__ stash_file; int /*<<< orphan*/  kadmind_port; scalar_t__ admin_server; scalar_t__ realm; } ;
typedef  TYPE_1__ kadm5_config_params ;
typedef  int /*<<< orphan*/  conf ;
struct TYPE_9__ {int num_strings; int /*<<< orphan*/ ** strings; } ;

/* Variables and functions */
 int /*<<< orphan*/  KADM5_ADMIN_SERVICE ; 
 int /*<<< orphan*/  KADM5_CONFIG_ADMIN_SERVER ; 
 int /*<<< orphan*/  KADM5_CONFIG_KADMIND_PORT ; 
 int /*<<< orphan*/  KADM5_CONFIG_REALM ; 
 int /*<<< orphan*/  KADM5_CONFIG_STASH_FILE ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIG_IGN ; 
 scalar_t__ ad_flag ; 
 scalar_t__ admin_server ; 
 int /*<<< orphan*/  args ; 
 int /*<<< orphan*/  asprintf (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_function ; 
 int /*<<< orphan*/  check_library ; 
 int /*<<< orphan*/ * client_name ; 
 int /*<<< orphan*/  commands ; 
 int /*<<< orphan*/ * config_file ; 
 int /*<<< orphan*/  context ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int exit_seen ; 
 scalar_t__ getarg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char**,int*) ; 
 int /*<<< orphan*/  hdb_db_dir (int /*<<< orphan*/ ) ; 
 scalar_t__ help_flag ; 
 int /*<<< orphan*/  htons (scalar_t__) ; 
 int kadm5_ad_init_with_password_ctx (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int kadm5_add_passwd_quality_verifier (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int kadm5_c_init_with_password_ctx (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int kadm5_c_init_with_skey_ctx (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kadm5_destroy (int /*<<< orphan*/ ) ; 
 int kadm5_s_init_with_password_ctx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kadm5_setup_passwd_quality_check (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kadm_handle ; 
 scalar_t__ keyfile ; 
 scalar_t__ keytab ; 
 int /*<<< orphan*/  krb5_err (int /*<<< orphan*/ ,int,int,char*) ; 
 int /*<<< orphan*/  krb5_errx (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  krb5_free_config_files (char**) ; 
 int /*<<< orphan*/  krb5_free_context (int /*<<< orphan*/ ) ; 
 int krb5_init_context (int /*<<< orphan*/ *) ; 
 int krb5_prepend_config_files_default (int /*<<< orphan*/ *,char***) ; 
 int krb5_set_config_files (int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  krb5_set_default_realm (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  krb5_warnx (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ local_flag ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  num_args ; 
 TYPE_2__ policy_libraries ; 
 int /*<<< orphan*/  print_version (int /*<<< orphan*/ *) ; 
 scalar_t__ realm ; 
 scalar_t__ server_port ; 
 int /*<<< orphan*/  setprogname (char*) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sl_command (int /*<<< orphan*/ ,int,char**) ; 
 int sl_command_loop (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usage (int) ; 
 scalar_t__ version_flag ; 

int
main(int argc, char **argv)
{
    krb5_error_code ret;
    char **files;
    kadm5_config_params conf;
    int optidx = 0;
    int exit_status = 0;

    setprogname(argv[0]);

    ret = krb5_init_context(&context);
    if (ret)
	errx (1, "krb5_init_context failed: %d", ret);

    if(getarg(args, num_args, argc, argv, &optidx))
	usage(1);

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

    memset(&conf, 0, sizeof(conf));
    if(realm) {
	krb5_set_default_realm(context, realm); /* XXX should be fixed
						   some other way */
	conf.realm = realm;
	conf.mask |= KADM5_CONFIG_REALM;
    }

    if (admin_server) {
	conf.admin_server = admin_server;
	conf.mask |= KADM5_CONFIG_ADMIN_SERVER;
    }

    if (server_port) {
	conf.kadmind_port = htons(server_port);
	conf.mask |= KADM5_CONFIG_KADMIND_PORT;
    }

    if (keyfile) {
	conf.stash_file = keyfile;
	conf.mask |= KADM5_CONFIG_STASH_FILE;
    }

    if(local_flag) {
	int i;

	kadm5_setup_passwd_quality_check (context,
					  check_library, check_function);

	for (i = 0; i < policy_libraries.num_strings; i++) {
	    ret = kadm5_add_passwd_quality_verifier(context,
						    policy_libraries.strings[i]);
	    if (ret)
		krb5_err(context, 1, ret, "kadm5_add_passwd_quality_verifier");
	}
	ret = kadm5_add_passwd_quality_verifier(context, NULL);
	if (ret)
	    krb5_err(context, 1, ret, "kadm5_add_passwd_quality_verifier");

	ret = kadm5_s_init_with_password_ctx(context,
					     KADM5_ADMIN_SERVICE,
					     NULL,
					     KADM5_ADMIN_SERVICE,
					     &conf, 0, 0,
					     &kadm_handle);
    } else if (ad_flag) {
	if (client_name == NULL)
	    krb5_errx(context, 1, "keytab mode require principal name");
	ret = kadm5_ad_init_with_password_ctx(context,
					      client_name,
					      NULL,
					      KADM5_ADMIN_SERVICE,
					      &conf, 0, 0,
					      &kadm_handle);
    } else if (keytab) {
	if (client_name == NULL)
	    krb5_errx(context, 1, "keytab mode require principal name");
        ret = kadm5_c_init_with_skey_ctx(context,
					 client_name,
					 keytab,
					 KADM5_ADMIN_SERVICE,
                                         &conf, 0, 0,
                                         &kadm_handle);
    } else
	ret = kadm5_c_init_with_password_ctx(context,
					     client_name,
					     NULL,
					     KADM5_ADMIN_SERVICE,
					     &conf, 0, 0,
					     &kadm_handle);

    if(ret)
	krb5_err(context, 1, ret, "kadm5_init_with_password");

    signal(SIGINT, SIG_IGN); /* ignore signals for now, the sl command
                                parser will handle SIGINT its own way;
                                we should really take care of this in
                                each function, f.i `get' might be
                                interruptable, but not `create' */
    if (argc != 0) {
	ret = sl_command (commands, argc, argv);
	if(ret == -1)
	    krb5_warnx (context, "unrecognized command: %s", argv[0]);
	else if (ret == -2)
	    ret = 0;
	if(ret != 0)
	    exit_status = 1;
    } else {
	while(!exit_seen) {
	    ret = sl_command_loop(commands, "kadmin> ", NULL);
	    if (ret == -2)
		exit_seen = 1;
	    else if (ret != 0)
		exit_status = 1;
	}
    }

    kadm5_destroy(kadm_handle);
    krb5_free_context(context);
    return exit_status;
}