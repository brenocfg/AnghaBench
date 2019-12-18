#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_9__ ;
typedef  struct TYPE_30__   TYPE_8__ ;
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_in {int /*<<< orphan*/  sin_addr; } ;
struct sockaddr {int dummy; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  remote ;
typedef  int /*<<< orphan*/  local ;
struct TYPE_24__ {TYPE_9__* authorization_data; } ;
struct TYPE_27__ {TYPE_2__ ticket; } ;
typedef  TYPE_5__ krb5_ticket ;
typedef  int /*<<< orphan*/  krb5_principal ;
typedef  scalar_t__ krb5_error_code ;
struct TYPE_28__ {char* data; int length; } ;
typedef  TYPE_6__ krb5_data ;
struct TYPE_29__ {int /*<<< orphan*/  session; TYPE_6__ ticket; int /*<<< orphan*/  client; int /*<<< orphan*/  server; } ;
typedef  TYPE_7__ krb5_creds ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  krb5_ccache ;
typedef  int /*<<< orphan*/  krb5_auth_context ;
struct TYPE_23__ {int length; int /*<<< orphan*/ * data; } ;
struct TYPE_30__ {TYPE_1__ address; void* addr_type; } ;
typedef  TYPE_8__ krb5_address ;
struct TYPE_31__ {int len; TYPE_4__* val; } ;
struct TYPE_25__ {scalar_t__ length; } ;
struct TYPE_26__ {int ad_type; TYPE_3__ ad_data; } ;
typedef  TYPE_9__ AuthorizationData ;

/* Variables and functions */
 void* AF_INET ; 
 int /*<<< orphan*/  VERSION ; 
 int /*<<< orphan*/  err (int,char*,char const*) ; 
 int /*<<< orphan*/  errx (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ getpeername (int,struct sockaddr*,int*) ; 
 scalar_t__ getsockname (int,struct sockaddr*,int*) ; 
 scalar_t__ krb5_auth_con_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_auth_con_setaddrs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_8__*,TYPE_8__*) ; 
 scalar_t__ krb5_auth_con_setuserkey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_cc_clear_mcred (TYPE_7__*) ; 
 scalar_t__ krb5_cc_default (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_cc_get_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_cc_retrieve_cred (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_7__*,TYPE_7__*) ; 
 int /*<<< orphan*/  krb5_data_free (TYPE_6__*) ; 
 int /*<<< orphan*/  krb5_data_zero (TYPE_6__*) ; 
 int /*<<< orphan*/  krb5_err (int /*<<< orphan*/ ,int,scalar_t__,char*) ; 
 scalar_t__ krb5_init_context (int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_make_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_mk_priv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*,TYPE_6__*,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_mk_safe (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*,TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_principal_get_realm (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_recvauth (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_5__**) ; 
 scalar_t__ krb5_unparse_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 scalar_t__ krb5_write_message (int /*<<< orphan*/ ,int*,TYPE_6__*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int strlen (char*) ; 

__attribute__((used)) static int
proto (int sock, const char *hostname, const char *service)
{
    struct sockaddr_in remote, local;
    socklen_t addrlen;
    krb5_address remote_addr, local_addr;
    krb5_context context;
    krb5_ccache ccache;
    krb5_auth_context auth_context;
    krb5_error_code status;
    krb5_principal client;
    krb5_data data;
    krb5_data packet;
    krb5_creds mcred, cred;
    krb5_ticket *ticket;

    addrlen = sizeof(local);
    if (getsockname (sock, (struct sockaddr *)&local, &addrlen) < 0
	|| addrlen != sizeof(local))
	err (1, "getsockname(%s)", hostname);

    addrlen = sizeof(remote);
    if (getpeername (sock, (struct sockaddr *)&remote, &addrlen) < 0
	|| addrlen != sizeof(remote))
	err (1, "getpeername(%s)", hostname);

    status = krb5_init_context(&context);
    if (status)
	errx(1, "krb5_init_context failed: %d", status);

    status = krb5_cc_default (context, &ccache);
    if (status)
	krb5_err(context, 1, status, "krb5_cc_default");

    status = krb5_auth_con_init (context, &auth_context);
    if (status)
	krb5_err(context, 1, status, "krb5_auth_con_init");

    local_addr.addr_type = AF_INET;
    local_addr.address.length = sizeof(local.sin_addr);
    local_addr.address.data   = &local.sin_addr;

    remote_addr.addr_type = AF_INET;
    remote_addr.address.length = sizeof(remote.sin_addr);
    remote_addr.address.data   = &remote.sin_addr;

    status = krb5_auth_con_setaddrs (context,
				     auth_context,
				     &local_addr,
				     &remote_addr);
    if (status)
	krb5_err(context, 1, status, "krb5_auth_con_setaddr");

    krb5_cc_clear_mcred(&mcred);

    status = krb5_cc_get_principal(context, ccache, &client);
    if(status)
	krb5_err(context, 1, status, "krb5_cc_get_principal");
    status = krb5_make_principal(context, &mcred.server,
				 krb5_principal_get_realm(context, client),
				 "krbtgt",
				 krb5_principal_get_realm(context, client),
				 NULL);
    if(status)
	krb5_err(context, 1, status, "krb5_make_principal");
    mcred.client = client;

    status = krb5_cc_retrieve_cred(context, ccache, 0, &mcred, &cred);
    if(status)
	krb5_err(context, 1, status, "krb5_cc_retrieve_cred");

    {
	char *client_name;
	krb5_data data;
	status = krb5_unparse_name(context, cred.client, &client_name);
	if(status)
	    krb5_err(context, 1, status, "krb5_unparse_name");
	data.data = client_name;
	data.length = strlen(client_name) + 1;
	status = krb5_write_message(context, &sock, &data);
	if(status)
	    krb5_err(context, 1, status, "krb5_write_message");
	free(client_name);
    }

    status = krb5_write_message(context, &sock, &cred.ticket);
    if(status)
	krb5_err(context, 1, status, "krb5_write_message");

    status = krb5_auth_con_setuserkey(context, auth_context, &cred.session);
    if(status)
	krb5_err(context, 1, status, "krb5_auth_con_setuserkey");

    status = krb5_recvauth(context, &auth_context, &sock,
			   VERSION, client, 0, NULL, &ticket);

    if (status)
	krb5_err(context, 1, status, "krb5_recvauth");

    if (ticket->ticket.authorization_data) {
	AuthorizationData *authz;
	int i;

	printf("Authorization data:\n");

	authz = ticket->ticket.authorization_data;
	for (i = 0; i < authz->len; i++) {
	    printf("\ttype %d, length %lu\n",
		   authz->val[i].ad_type,
		   (unsigned long)authz->val[i].ad_data.length);
	}
    }

    data.data   = "hej";
    data.length = 3;

    krb5_data_zero (&packet);

    status = krb5_mk_safe (context,
			   auth_context,
			   &data,
			   &packet,
			   NULL);
    if (status)
	krb5_err(context, 1, status, "krb5_mk_safe");

    status = krb5_write_message(context, &sock, &packet);
    if(status)
	krb5_err(context, 1, status, "krb5_write_message");

    data.data   = "hemligt";
    data.length = 7;

    krb5_data_free (&packet);

    status = krb5_mk_priv (context,
			   auth_context,
			   &data,
			   &packet,
			   NULL);
    if (status)
	krb5_err(context, 1, status, "krb5_mk_priv");

    status = krb5_write_message(context, &sock, &packet);
    if(status)
	krb5_err(context, 1, status, "krb5_write_message");
    return 0;
}