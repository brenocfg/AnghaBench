#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_20__ ;
typedef  struct TYPE_25__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_storage {int dummy; } ;
struct sockaddr {int /*<<< orphan*/  sa_family; } ;
typedef  int /*<<< orphan*/  ss ;
typedef  int socklen_t ;
struct TYPE_25__ {int /*<<< orphan*/  server; } ;
typedef  TYPE_1__ krb5_ticket ;
typedef  int /*<<< orphan*/  krb5_socket_t ;
typedef  int /*<<< orphan*/  krb5_principal ;
typedef  int /*<<< orphan*/  krb5_log_facility ;
typedef  int /*<<< orphan*/  krb5_keytab ;
typedef  scalar_t__ krb5_error_code ;
struct TYPE_27__ {scalar_t__ length; int /*<<< orphan*/ * data; } ;
typedef  TYPE_2__ krb5_data ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  TYPE_3__* krb5_authenticator ;
typedef  int /*<<< orphan*/ * krb5_auth_context ;
struct TYPE_26__ {int /*<<< orphan*/  principal; } ;
struct TYPE_29__ {TYPE_20__ entry; } ;
typedef  TYPE_4__ hdb_entry_ex ;
typedef  int /*<<< orphan*/  entry ;
typedef  int /*<<< orphan*/  addr_name ;
struct TYPE_30__ {scalar_t__ (* hdb_store ) (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ,TYPE_4__*) ;scalar_t__ (* hdb_rename ) (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ *) ;scalar_t__ (* hdb_close ) (int /*<<< orphan*/ ,TYPE_5__*) ;scalar_t__ (* hdb_open ) (int /*<<< orphan*/ ,TYPE_5__*,int,int) ;} ;
struct TYPE_28__ {int /*<<< orphan*/  crealm; int /*<<< orphan*/  cname; } ;
typedef  TYPE_5__ HDB ;

/* Variables and functions */
 scalar_t__ HDB_ERR_EXISTS ; 
 scalar_t__ HEIM_ERR_EOF ; 
 int /*<<< orphan*/  HPROP_PORT ; 
 int /*<<< orphan*/  HPROP_VERSION ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int O_TRUNC ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  _krb5_principalname2krb5_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  args ; 
 int /*<<< orphan*/  asprintf (char**,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * database ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ from_stdin ; 
 scalar_t__ getarg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char**,int*) ; 
 scalar_t__ getpeername (int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 scalar_t__ hdb_create (int /*<<< orphan*/ ,TYPE_5__**,char*) ; 
 int /*<<< orphan*/ * hdb_default_db (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdb_free_entry (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  hdb_kt_ops ; 
 int /*<<< orphan*/  hdb_print_entry (int /*<<< orphan*/ ,TYPE_5__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ hdb_value2entry (int /*<<< orphan*/ ,TYPE_2__*,TYPE_20__*) ; 
 scalar_t__ help_flag ; 
 int /*<<< orphan*/ * inet_ntop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int inetd_flag ; 
 scalar_t__ krb5_auth_con_getauthenticator (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__**) ; 
 int /*<<< orphan*/  krb5_data_free (TYPE_2__*) ; 
 int /*<<< orphan*/  krb5_err (int /*<<< orphan*/ ,int,scalar_t__,char*,...) ; 
 int /*<<< orphan*/  krb5_errx (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  krb5_free_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_free_ticket (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  krb5_getportbyname (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_init_context (int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_kt_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_kt_default (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_kt_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_kt_resolve (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_log (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ krb5_make_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_openlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  krb5_principal_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_read_message (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ krb5_read_priv_message (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ krb5_recvauth (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  krb5_set_default_realm (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_set_warn_dest (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_unparse_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  krb5_warnx (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  krb5_write_priv_message (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/ * ktname ; 
 int /*<<< orphan*/ * local_realm ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mini_inetd (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  num_args ; 
 scalar_t__ print_dump ; 
 int /*<<< orphan*/  print_version (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rk_INVALID_SOCKET ; 
 int /*<<< orphan*/  rk_closesocket (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setprogname (char*) ; 
 int /*<<< orphan*/  socket_get_address (struct sockaddr*) ; 
 int /*<<< orphan*/  stdout ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,TYPE_5__*,int,int) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,TYPE_5__*) ; 
 scalar_t__ stub3 (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ *) ; 
 scalar_t__ stub4 (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ,TYPE_4__*) ; 
 char* unparseable_name ; 
 int /*<<< orphan*/  usage (int) ; 
 scalar_t__ version_flag ; 

int
main(int argc, char **argv)
{
    krb5_error_code ret;
    krb5_context context;
    krb5_auth_context ac = NULL;
    krb5_principal c1, c2;
    krb5_authenticator authent;
    krb5_keytab keytab;
    krb5_socket_t sock = rk_INVALID_SOCKET;
    HDB *db = NULL;
    int optidx = 0;
    char *tmp_db;
    krb5_log_facility *fac;
    int nprincs;

    setprogname(argv[0]);

    ret = krb5_init_context(&context);
    if(ret)
	exit(1);

    ret = krb5_openlog(context, "hpropd", &fac);
    if(ret)
	errx(1, "krb5_openlog");
    krb5_set_warn_dest(context, fac);

    if(getarg(args, num_args, argc, argv, &optidx))
	usage(1);

    if(local_realm != NULL)
	krb5_set_default_realm(context, local_realm);

    if(help_flag)
	usage(0);
    if(version_flag) {
	print_version(NULL);
	exit(0);
    }

    argc -= optidx;
    argv += optidx;

    if (argc != 0)
	usage(1);

    if (database == NULL)
	database = hdb_default_db(context);

    if(from_stdin) {
	sock = STDIN_FILENO;
    } else {
	struct sockaddr_storage ss;
	struct sockaddr *sa = (struct sockaddr *)&ss;
	socklen_t sin_len = sizeof(ss);
	char addr_name[256];
	krb5_ticket *ticket;
	char *server;

	sock = STDIN_FILENO;
#ifdef SUPPORT_INETD
	if (inetd_flag == -1) {
	    if (getpeername (sock, sa, &sin_len) < 0) {
		inetd_flag = 0;
	    } else {
		inetd_flag = 1;
	    }
	}
#else
	inetd_flag = 0;
#endif
	if (!inetd_flag) {
	    mini_inetd (krb5_getportbyname (context, "hprop", "tcp",
					    HPROP_PORT), &sock);
	}
	sin_len = sizeof(ss);
	if(getpeername(sock, sa, &sin_len) < 0)
	    krb5_err(context, 1, errno, "getpeername");

	if (inet_ntop(sa->sa_family,
		      socket_get_address (sa),
		      addr_name,
		      sizeof(addr_name)) == NULL)
	    strlcpy (addr_name, "unknown address",
		     sizeof(addr_name));

	krb5_log(context, fac, 0, "Connection from %s", addr_name);

	ret = krb5_kt_register(context, &hdb_kt_ops);
	if(ret)
	    krb5_err(context, 1, ret, "krb5_kt_register");

	if (ktname != NULL) {
	    ret = krb5_kt_resolve(context, ktname, &keytab);
	    if (ret)
		krb5_err (context, 1, ret, "krb5_kt_resolve %s", ktname);
	} else {
	    ret = krb5_kt_default (context, &keytab);
	    if (ret)
		krb5_err (context, 1, ret, "krb5_kt_default");
	}

	ret = krb5_recvauth(context, &ac, &sock, HPROP_VERSION, NULL,
			    0, keytab, &ticket);
	if(ret)
	    krb5_err(context, 1, ret, "krb5_recvauth");

	ret = krb5_unparse_name(context, ticket->server, &server);
	if (ret)
	    krb5_err(context, 1, ret, "krb5_unparse_name");
	if (strncmp(server, "hprop/", 5) != 0)
	    krb5_errx(context, 1, "ticket not for hprop (%s)", server);

	free(server);
	krb5_free_ticket (context, ticket);

	ret = krb5_auth_con_getauthenticator(context, ac, &authent);
	if(ret)
	    krb5_err(context, 1, ret, "krb5_auth_con_getauthenticator");

	ret = krb5_make_principal(context, &c1, NULL, "kadmin", "hprop", NULL);
	if(ret)
	    krb5_err(context, 1, ret, "krb5_make_principal");
	_krb5_principalname2krb5_principal(context, &c2,
					   authent->cname, authent->crealm);
	if(!krb5_principal_compare(context, c1, c2)) {
	    char *s;
	    ret = krb5_unparse_name(context, c2, &s);
	    if (ret)
		s = unparseable_name;
	    krb5_errx(context, 1, "Unauthorized connection from %s", s);
	}
	krb5_free_principal(context, c1);
	krb5_free_principal(context, c2);

	ret = krb5_kt_close(context, keytab);
	if(ret)
	    krb5_err(context, 1, ret, "krb5_kt_close");
    }

    if(!print_dump) {
	asprintf(&tmp_db, "%s~", database);

	ret = hdb_create(context, &db, tmp_db);
	if(ret)
	    krb5_err(context, 1, ret, "hdb_create(%s)", tmp_db);
	ret = db->hdb_open(context, db, O_RDWR | O_CREAT | O_TRUNC, 0600);
	if(ret)
	    krb5_err(context, 1, ret, "hdb_open(%s)", tmp_db);
    }

    nprincs = 0;
    while(1){
	krb5_data data;
	hdb_entry_ex entry;

	if(from_stdin) {
	    ret = krb5_read_message(context, &sock, &data);
	    if(ret != 0 && ret != HEIM_ERR_EOF)
		krb5_err(context, 1, ret, "krb5_read_message");
	} else {
	    ret = krb5_read_priv_message(context, ac, &sock, &data);
	    if(ret)
		krb5_err(context, 1, ret, "krb5_read_priv_message");
	}

	if(ret == HEIM_ERR_EOF || data.length == 0) {
	    if(!from_stdin) {
		data.data = NULL;
		data.length = 0;
		krb5_write_priv_message(context, ac, &sock, &data);
	    }
	    if(!print_dump) {
		ret = db->hdb_close(context, db);
		if(ret)
		    krb5_err(context, 1, ret, "db_close");
		ret = db->hdb_rename(context, db, database);
		if(ret)
		    krb5_err(context, 1, ret, "db_rename");
	    }
	    break;
	}
	memset(&entry, 0, sizeof(entry));
	ret = hdb_value2entry(context, &data, &entry.entry);
	krb5_data_free(&data);
	if(ret)
	    krb5_err(context, 1, ret, "hdb_value2entry");
	if(print_dump)
	    hdb_print_entry(context, db, &entry, stdout);
	else {
	    ret = db->hdb_store(context, db, 0, &entry);
	    if(ret == HDB_ERR_EXISTS) {
		char *s;
		ret = krb5_unparse_name(context, entry.entry.principal, &s);
		if (ret)
		    s = strdup(unparseable_name);
		krb5_warnx(context, "Entry exists: %s", s);
		free(s);
	    } else if(ret)
		krb5_err(context, 1, ret, "db_store");
	    else
		nprincs++;
	}
	hdb_free_entry(context, &entry);
    }
    if (!print_dump)
	krb5_log(context, fac, 0, "Received %d principals", nprincs);

    if (inetd_flag == 0)
	rk_closesocket(sock);

    exit(0);
}