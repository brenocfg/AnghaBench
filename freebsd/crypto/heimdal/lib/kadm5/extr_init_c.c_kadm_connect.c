#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct addrinfo {int /*<<< orphan*/  ai_addrlen; int /*<<< orphan*/  ai_addr; int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_family; scalar_t__ realm; int /*<<< orphan*/  mask; struct addrinfo* ai_next; } ;
typedef  scalar_t__ rk_socket_t ;
typedef  int /*<<< orphan*/  portstr ;
typedef  int /*<<< orphan*/  p ;
typedef  int /*<<< orphan*/  krb5_principal ;
typedef  int /*<<< orphan*/  krb5_data ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  krb5_ccache ;
typedef  scalar_t__ kadm5_ret_t ;
typedef  struct addrinfo kadm5_config_params ;
struct TYPE_3__ {char* admin_server; scalar_t__ sock; int /*<<< orphan*/ * ccache; int /*<<< orphan*/ * ac; scalar_t__ realm; int /*<<< orphan*/  keytab; int /*<<< orphan*/  prompter; int /*<<< orphan*/  service_name; int /*<<< orphan*/  client_name; int /*<<< orphan*/  kadmind_port; int /*<<< orphan*/  context; } ;
typedef  TYPE_1__ kadm5_client_context ;
typedef  int /*<<< orphan*/  hints ;

/* Variables and functions */
 int /*<<< orphan*/  AP_OPTS_MUTUAL_REQUIRED ; 
 scalar_t__ ENOMEM ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  KADM5_ADMIN_SERVICE ; 
 scalar_t__ KADM5_BAD_SERVER_NAME ; 
 int /*<<< orphan*/  KADM5_CONFIG_REALM ; 
 scalar_t__ KADM5_FAILURE ; 
 int /*<<< orphan*/  KADMIN_APPL_VERSION ; 
 int /*<<< orphan*/  KADMIN_OLD_APPL_VERSION ; 
 scalar_t__ KRB5_SENDAUTH_BADAPPLVERS ; 
 int NI_MAXSERV ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 scalar_t__ _kadm5_c_get_cred_cache (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ _kadm5_marshal_params (int /*<<< orphan*/ ,struct addrinfo*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  asprintf (char**,char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ connect (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int getaddrinfo (char*,char*,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/  krb5_cc_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_clear_error_message (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_data_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_free_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_parse_name (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_sendauth (int /*<<< orphan*/ ,int /*<<< orphan*/ **,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_warn (int /*<<< orphan*/ ,scalar_t__,char*,char*) ; 
 int /*<<< orphan*/  krb5_warnx (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ krb5_write_priv_message (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 scalar_t__ rk_INVALID_SOCKET ; 
 int /*<<< orphan*/  rk_closesocket (scalar_t__) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 scalar_t__ socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static kadm5_ret_t
kadm_connect(kadm5_client_context *ctx)
{
    kadm5_ret_t ret;
    krb5_principal server;
    krb5_ccache cc;
    rk_socket_t s = rk_INVALID_SOCKET;
    struct addrinfo *ai, *a;
    struct addrinfo hints;
    int error;
    char portstr[NI_MAXSERV];
    char *hostname, *slash;
    char *service_name;
    krb5_context context = ctx->context;

    memset (&hints, 0, sizeof(hints));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    snprintf (portstr, sizeof(portstr), "%u", ntohs(ctx->kadmind_port));

    hostname = ctx->admin_server;
    slash = strchr (hostname, '/');
    if (slash != NULL)
	hostname = slash + 1;

    error = getaddrinfo (hostname, portstr, &hints, &ai);
    if (error) {
	krb5_clear_error_message(context);
	return KADM5_BAD_SERVER_NAME;
    }

    for (a = ai; a != NULL; a = a->ai_next) {
	s = socket (a->ai_family, a->ai_socktype, a->ai_protocol);
	if (s < 0)
	    continue;
	if (connect (s, a->ai_addr, a->ai_addrlen) < 0) {
	    krb5_clear_error_message(context);
	    krb5_warn (context, errno, "connect(%s)", hostname);
	    rk_closesocket (s);
	    continue;
	}
	break;
    }
    if (a == NULL) {
	freeaddrinfo (ai);
	krb5_clear_error_message(context);
	krb5_warnx (context, "failed to contact %s", hostname);
	return KADM5_FAILURE;
    }
    ret = _kadm5_c_get_cred_cache(context,
				  ctx->client_name,
				  ctx->service_name,
				  NULL, ctx->prompter, ctx->keytab,
				  ctx->ccache, &cc);

    if(ret) {
	freeaddrinfo (ai);
	rk_closesocket(s);
	return ret;
    }

    if (ctx->realm)
	asprintf(&service_name, "%s@%s", KADM5_ADMIN_SERVICE, ctx->realm);
    else
	asprintf(&service_name, "%s", KADM5_ADMIN_SERVICE);

    if (service_name == NULL) {
	freeaddrinfo (ai);
	rk_closesocket(s);
	krb5_clear_error_message(context);
	return ENOMEM;
    }

    ret = krb5_parse_name(context, service_name, &server);
    free(service_name);
    if(ret) {
	freeaddrinfo (ai);
	if(ctx->ccache == NULL)
	    krb5_cc_close(context, cc);
	rk_closesocket(s);
	return ret;
    }
    ctx->ac = NULL;

    ret = krb5_sendauth(context, &ctx->ac, &s,
			KADMIN_APPL_VERSION, NULL,
			server, AP_OPTS_MUTUAL_REQUIRED,
			NULL, NULL, cc, NULL, NULL, NULL);
    if(ret == 0) {
	krb5_data params;
	kadm5_config_params p;
	memset(&p, 0, sizeof(p));
	if(ctx->realm) {
	    p.mask |= KADM5_CONFIG_REALM;
	    p.realm = ctx->realm;
	}
	ret = _kadm5_marshal_params(context, &p, &params);

	ret = krb5_write_priv_message(context, ctx->ac, &s, &params);
	krb5_data_free(&params);
	if(ret) {
	    freeaddrinfo (ai);
	    rk_closesocket(s);
	    if(ctx->ccache == NULL)
		krb5_cc_close(context, cc);
	    return ret;
	}
    } else if(ret == KRB5_SENDAUTH_BADAPPLVERS) {
	rk_closesocket(s);

	s = socket (a->ai_family, a->ai_socktype, a->ai_protocol);
	if (s < 0) {
	    freeaddrinfo (ai);
	    krb5_clear_error_message(context);
	    return errno;
	}
	if (connect (s, a->ai_addr, a->ai_addrlen) < 0) {
	    rk_closesocket (s);
	    freeaddrinfo (ai);
	    krb5_clear_error_message(context);
	    return errno;
	}
	ret = krb5_sendauth(context, &ctx->ac, &s,
			    KADMIN_OLD_APPL_VERSION, NULL,
			    server, AP_OPTS_MUTUAL_REQUIRED,
			    NULL, NULL, cc, NULL, NULL, NULL);
    }
    freeaddrinfo (ai);
    if(ret) {
	rk_closesocket(s);
	return ret;
    }

    krb5_free_principal(context, server);
    if(ctx->ccache == NULL)
	krb5_cc_close(context, cc);
    ctx->sock = s;

    return 0;
}