#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vers ;
typedef  scalar_t__ uint32_t ;
struct timeval {int member_0; int /*<<< orphan*/  member_1; } ;
struct sockaddr_un {int dummy; } ;
struct sockaddr_storage {int dummy; } ;
struct sockaddr {int dummy; } ;
typedef  int socklen_t ;
struct TYPE_16__ {int flags; int /*<<< orphan*/  fd; struct TYPE_16__* next; } ;
typedef  TYPE_2__ slave ;
typedef  int /*<<< orphan*/  peer_addr ;
typedef  int /*<<< orphan*/  krb5_socket_t ;
typedef  int /*<<< orphan*/  krb5_keytab ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_15__ {int /*<<< orphan*/  log_file; } ;
struct TYPE_17__ {TYPE_1__ log_context; } ;
typedef  TYPE_3__ kadm5_server_context ;
struct TYPE_18__ {scalar_t__ realm; int /*<<< orphan*/  mask; } ;
typedef  TYPE_4__ kadm5_config_params ;
typedef  int /*<<< orphan*/  fd_set ;
typedef  int /*<<< orphan*/  conf ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 scalar_t__ FD_ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SETSIZE ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KADM5_ADMIN_SERVICE ; 
 int /*<<< orphan*/  KADM5_CONFIG_REALM ; 
 int /*<<< orphan*/  O_RDONLY ; 
 scalar_t__ SIGINT ; 
 scalar_t__ SIGTERM ; 
 scalar_t__ SIGXCPU ; 
 int SLAVE_F_DEAD ; 
 int /*<<< orphan*/  add_slave (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  args ; 
 int /*<<< orphan*/  asprintf (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * config_file ; 
 int /*<<< orphan*/  daemon (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  database ; 
 scalar_t__ detach_from_console ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ exit_flag ; 
 unsigned long getprogname () ; 
 int /*<<< orphan*/  hdb_db_dir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdb_kt_ops ; 
 scalar_t__ help_flag ; 
 scalar_t__ kadm5_init_with_skey_ctx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  kadm5_log_get_version_fd (int,scalar_t__*) ; 
 int /*<<< orphan*/  keytab_str ; 
 int /*<<< orphan*/  krb5_err (int /*<<< orphan*/ ,int,scalar_t__,char*,...) ; 
 int /*<<< orphan*/  krb5_errx (int /*<<< orphan*/ ,int,char*,...) ; 
 int /*<<< orphan*/  krb5_free_config_files (char**) ; 
 scalar_t__ krb5_kt_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_kt_resolve (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_openlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_prepend_config_files_default (int /*<<< orphan*/ *,char***) ; 
 int krb5_program_setup (int /*<<< orphan*/ *,int,char**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_set_config_files (int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  krb5_set_warn_dest (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_std_usage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_warn (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int /*<<< orphan*/  krb5_warnx (int /*<<< orphan*/ ,char*,unsigned long,...) ; 
 int /*<<< orphan*/  log_facility ; 
 int /*<<< orphan*/  make_listen6_socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_listen_socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_signal_socket (int /*<<< orphan*/ ) ; 
 int max (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  num_args ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ parse_time (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pidfile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  port_str ; 
 int /*<<< orphan*/  print_version (int /*<<< orphan*/ *) ; 
 scalar_t__ process_msg (int /*<<< orphan*/ ,TYPE_2__*,int,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ realm ; 
 scalar_t__ recvfrom (int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 scalar_t__ select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  send_are_you_there (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  send_diffs (int /*<<< orphan*/ ,TYPE_2__*,int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  setup_signal () ; 
 int /*<<< orphan*/  slave_dead (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ slave_gone_p (TYPE_2__*) ; 
 scalar_t__ slave_missing_p (TYPE_2__*) ; 
 int /*<<< orphan*/  slave_time_gone ; 
 int /*<<< orphan*/  slave_time_missing ; 
 scalar_t__ time_before_gone ; 
 scalar_t__ time_before_missing ; 
 scalar_t__ version_flag ; 
 int /*<<< orphan*/  write_master_down (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_stats (int /*<<< orphan*/ ,TYPE_2__*,scalar_t__) ; 

int
main(int argc, char **argv)
{
    krb5_error_code ret;
    krb5_context context;
    void *kadm_handle;
    kadm5_server_context *server_context;
    kadm5_config_params conf;
    krb5_socket_t signal_fd, listen_fd, listen6_fd;
    int log_fd;
    slave *slaves = NULL;
    uint32_t current_version = 0, old_version = 0;
    krb5_keytab keytab;
    int optidx;
    char **files;

    optidx = krb5_program_setup(&context, argc, argv, args, num_args, NULL);

    if(help_flag)
	krb5_std_usage(0, args, num_args);
    if(version_flag) {
	print_version(NULL);
	exit(0);
    }

    setup_signal();

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

    time_before_gone = parse_time (slave_time_gone,  "s");
    if (time_before_gone < 0)
	krb5_errx (context, 1, "couldn't parse time: %s", slave_time_gone);
    time_before_missing = parse_time (slave_time_missing,  "s");
    if (time_before_missing < 0)
	krb5_errx (context, 1, "couldn't parse time: %s", slave_time_missing);

#ifdef SUPPORT_DETACH
    if (detach_from_console)
	daemon(0, 0);
#endif
    pidfile (NULL);
    krb5_openlog (context, "ipropd-master", &log_facility);
    krb5_set_warn_dest(context, log_facility);

    ret = krb5_kt_register(context, &hdb_kt_ops);
    if(ret)
	krb5_err(context, 1, ret, "krb5_kt_register");

    ret = krb5_kt_resolve(context, keytab_str, &keytab);
    if(ret)
	krb5_err(context, 1, ret, "krb5_kt_resolve: %s", keytab_str);

    memset(&conf, 0, sizeof(conf));
    if(realm) {
	conf.mask |= KADM5_CONFIG_REALM;
	conf.realm = realm;
    }
    ret = kadm5_init_with_skey_ctx (context,
				    KADM5_ADMIN_SERVICE,
				    NULL,
				    KADM5_ADMIN_SERVICE,
				    &conf, 0, 0,
				    &kadm_handle);
    if (ret)
	krb5_err (context, 1, ret, "kadm5_init_with_password_ctx");

    server_context = (kadm5_server_context *)kadm_handle;

    log_fd = open (server_context->log_context.log_file, O_RDONLY, 0);
    if (log_fd < 0)
	krb5_err (context, 1, errno, "open %s",
		  server_context->log_context.log_file);

    signal_fd = make_signal_socket (context);
    listen_fd = make_listen_socket (context, port_str);
    listen6_fd = make_listen6_socket (context, port_str);

    kadm5_log_get_version_fd (log_fd, &current_version);

    krb5_warnx(context, "ipropd-master started at version: %lu",
	       (unsigned long)current_version);

    while(exit_flag == 0){
	slave *p;
	fd_set readset;
	int max_fd = 0;
	struct timeval to = {30, 0};
	uint32_t vers;

#ifndef NO_LIMIT_FD_SETSIZE
	if (signal_fd >= FD_SETSIZE || listen_fd >= FD_SETSIZE ||
	    listen6_fd >= FD_SETSIZE)
	    krb5_errx (context, 1, "fd too large");
#endif

	FD_ZERO(&readset);
	FD_SET(signal_fd, &readset);
	max_fd = max(max_fd, signal_fd);
	FD_SET(listen_fd, &readset);
	max_fd = max(max_fd, listen_fd);
	FD_SET(listen6_fd, &readset);
	max_fd = max(max_fd, listen6_fd);

	for (p = slaves; p != NULL; p = p->next) {
	    if (p->flags & SLAVE_F_DEAD)
		continue;
	    FD_SET(p->fd, &readset);
	    max_fd = max(max_fd, p->fd);
	}

	ret = select (max_fd + 1,
		      &readset, NULL, NULL, &to);
	if (ret < 0) {
	    if (errno == EINTR)
		continue;
	    else
		krb5_err (context, 1, errno, "select");
	}

	if (ret == 0) {
	    old_version = current_version;
	    kadm5_log_get_version_fd (log_fd, &current_version);

	    if (current_version > old_version) {
		krb5_warnx(context,
			   "Missed a signal, updating slaves %lu to %lu",
			   (unsigned long)old_version,
			   (unsigned long)current_version);
		for (p = slaves; p != NULL; p = p->next) {
		    if (p->flags & SLAVE_F_DEAD)
			continue;
		    send_diffs (context, p, log_fd, database, current_version);
		}
	    }
	}

	if (ret && FD_ISSET(signal_fd, &readset)) {
#ifndef NO_UNIX_SOCKETS
	    struct sockaddr_un peer_addr;
#else
	    struct sockaddr_storage peer_addr;
#endif
	    socklen_t peer_len = sizeof(peer_addr);

	    if(recvfrom(signal_fd, (void *)&vers, sizeof(vers), 0,
			(struct sockaddr *)&peer_addr, &peer_len) < 0) {
		krb5_warn (context, errno, "recvfrom");
		continue;
	    }
	    --ret;
	    assert(ret >= 0);
	    old_version = current_version;
	    kadm5_log_get_version_fd (log_fd, &current_version);
	    if (current_version > old_version) {
		krb5_warnx(context,
			   "Got a signal, updating slaves %lu to %lu",
			   (unsigned long)old_version,
			   (unsigned long)current_version);
		for (p = slaves; p != NULL; p = p->next) {
		    if (p->flags & SLAVE_F_DEAD)
			continue;
		    send_diffs (context, p, log_fd, database, current_version);
		}
	    } else {
		krb5_warnx(context,
			   "Got a signal, but no update in log version %lu",
			   (unsigned long)current_version);
	    }
        }

	for(p = slaves; p != NULL; p = p->next) {
	    if (p->flags & SLAVE_F_DEAD)
	        continue;
	    if (ret && FD_ISSET(p->fd, &readset)) {
		--ret;
		assert(ret >= 0);
		if(process_msg (context, p, log_fd, database, current_version))
		    slave_dead(context, p);
	    } else if (slave_gone_p (p))
		slave_dead(context, p);
	    else if (slave_missing_p (p))
		send_are_you_there (context, p);
	}

	if (ret && FD_ISSET(listen6_fd, &readset)) {
	    add_slave (context, keytab, &slaves, listen6_fd);
	    --ret;
	    assert(ret >= 0);
	}
	if (ret && FD_ISSET(listen_fd, &readset)) {
	    add_slave (context, keytab, &slaves, listen_fd);
	    --ret;
	    assert(ret >= 0);
	}
	write_stats(context, slaves, current_version);
    }

    if(exit_flag == SIGINT || exit_flag == SIGTERM)
	krb5_warnx(context, "%s terminated", getprogname());
#ifdef SIGXCPU
    else if(exit_flag == SIGXCPU)
	krb5_warnx(context, "%s CPU time limit exceeded", getprogname());
#endif
    else
	krb5_warnx(context, "%s unexpected exit reason: %ld",
		   getprogname(), (long)exit_flag);

    write_master_down(context);

    return 0;
}