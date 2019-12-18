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
struct prop_data {int sock; int /*<<< orphan*/ * auth_context; int /*<<< orphan*/  context; } ;
typedef  int /*<<< orphan*/  portstr ;
typedef  int /*<<< orphan*/  krb5_realm ;
typedef  int /*<<< orphan*/  krb5_principal ;
typedef  int /*<<< orphan*/  krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_data ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  krb5_ccache ;
typedef  int /*<<< orphan*/ * krb5_auth_context ;
typedef  int /*<<< orphan*/  HDB ;

/* Variables and functions */
 int AP_OPTS_MUTUAL_REQUIRED ; 
 int AP_OPTS_USE_SUBKEY ; 
 int /*<<< orphan*/  HPROP_NAME ; 
 int /*<<< orphan*/  HPROP_PORT ; 
 int /*<<< orphan*/  HPROP_VERSION ; 
 int /*<<< orphan*/  KRB5_NT_SRV_HST ; 
 int NI_MAXSERV ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  iterate (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int,struct prop_data*) ; 
 int /*<<< orphan*/  krb5_auth_con_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_data_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_data_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_free_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_get_default_realm (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_getportbyname (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_principal_set_realm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_read_priv_message (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_sendauth (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_sname_to_principal (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_warn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  krb5_warnx (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  krb5_write_priv_message (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_xfree (int /*<<< orphan*/ ) ; 
 scalar_t__ local_realm ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int open_socket (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static int
propagate_database (krb5_context context, int type,
		    const char *database_name,
		    HDB *db, krb5_ccache ccache,
		    int optidx, int argc, char **argv)
{
    krb5_principal server;
    krb5_error_code ret;
    int i, failed = 0;

    for(i = optidx; i < argc; i++){
	krb5_auth_context auth_context;
	int fd;
	struct prop_data pd;
	krb5_data data;

	char *port, portstr[NI_MAXSERV];
	char *host = argv[i];

	port = strchr(host, ':');
	if(port == NULL) {
	    snprintf(portstr, sizeof(portstr), "%u",
		     ntohs(krb5_getportbyname (context, "hprop", "tcp",
					       HPROP_PORT)));
	    port = portstr;
	} else
	    *port++ = '\0';

	fd = open_socket(context, host, port);
	if(fd < 0) {
	    failed++;
	    krb5_warn (context, errno, "connect %s", host);
	    continue;
	}

	ret = krb5_sname_to_principal(context, argv[i],
				      HPROP_NAME, KRB5_NT_SRV_HST, &server);
	if(ret) {
	    failed++;
	    krb5_warn(context, ret, "krb5_sname_to_principal(%s)", host);
	    close(fd);
	    continue;
	}

        if (local_realm) {
            krb5_realm my_realm;
            krb5_get_default_realm(context,&my_realm);
            krb5_principal_set_realm(context,server,my_realm);
	    krb5_xfree(my_realm);
        }

	auth_context = NULL;
	ret = krb5_sendauth(context,
			    &auth_context,
			    &fd,
			    HPROP_VERSION,
			    NULL,
			    server,
			    AP_OPTS_MUTUAL_REQUIRED | AP_OPTS_USE_SUBKEY,
			    NULL, /* in_data */
			    NULL, /* in_creds */
			    ccache,
			    NULL,
			    NULL,
			    NULL);

	krb5_free_principal(context, server);

	if(ret) {
	    failed++;
	    krb5_warn(context, ret, "krb5_sendauth (%s)", host);
	    close(fd);
	    goto next_host;
	}

	pd.context      = context;
	pd.auth_context = auth_context;
	pd.sock         = fd;

	ret = iterate (context, database_name, db, type, &pd);
	if (ret) {
	    krb5_warnx(context, "iterate to host %s failed", host);
	    failed++;
	    goto next_host;
	}

	krb5_data_zero (&data);
	ret = krb5_write_priv_message(context, auth_context, &fd, &data);
	if(ret) {
	    krb5_warn(context, ret, "krb5_write_priv_message");
	    failed++;
	    goto next_host;
	}

	ret = krb5_read_priv_message(context, auth_context, &fd, &data);
	if(ret) {
	    krb5_warn(context, ret, "krb5_read_priv_message: %s", host);
	    failed++;
	    goto next_host;
	} else
	    krb5_data_free (&data);

    next_host:
	krb5_auth_con_free(context, auth_context);
	close(fd);
    }
    if (failed)
	return 1;
    return 0;
}