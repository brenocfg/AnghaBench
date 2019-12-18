#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  realm_params ;
struct TYPE_6__ {int /*<<< orphan*/  initial; } ;
struct TYPE_7__ {TYPE_1__ flags; } ;
struct TYPE_8__ {int /*<<< orphan*/  client; TYPE_2__ ticket; int /*<<< orphan*/  server; } ;
typedef  TYPE_3__ krb5_ticket ;
typedef  int /*<<< orphan*/  krb5_socket_t ;
typedef  int /*<<< orphan*/  krb5_keytab ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_data ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  krb5_boolean ;
typedef  int /*<<< orphan*/ * krb5_auth_context ;
typedef  int /*<<< orphan*/  kadm5_config_params ;

/* Variables and functions */
 int /*<<< orphan*/  KADM5_ADMIN_SERVICE ; 
 int /*<<< orphan*/  KRB5_RECVAUTH_IGNORE_VERSION ; 
 int /*<<< orphan*/  _kadm5_unmarshal_params (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ kadm5_s_init_with_password_ctx (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  krb5_err (int /*<<< orphan*/ ,int,scalar_t__,char*) ; 
 int /*<<< orphan*/  krb5_errx (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  krb5_free_ticket (int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ krb5_read_priv_message (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_recvauth_match_version (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__**) ; 
 scalar_t__ krb5_unparse_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  match_appl_version ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v5_loop (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
handle_v5(krb5_context contextp,
	  krb5_keytab keytab,
	  krb5_socket_t fd)
{
    krb5_error_code ret;
    krb5_ticket *ticket;
    char *server_name;
    char *client;
    void *kadm_handlep;
    krb5_boolean initial;
    krb5_auth_context ac = NULL;

    unsigned kadm_version;
    kadm5_config_params realm_params;

    ret = krb5_recvauth_match_version(contextp, &ac, &fd,
				      match_appl_version, &kadm_version,
				      NULL, KRB5_RECVAUTH_IGNORE_VERSION,
				      keytab, &ticket);
    if (ret)
	krb5_err(contextp, 1, ret, "krb5_recvauth");

    ret = krb5_unparse_name (contextp, ticket->server, &server_name);
    if (ret)
	krb5_err (contextp, 1, ret, "krb5_unparse_name");

    if (strncmp (server_name, KADM5_ADMIN_SERVICE,
		 strlen(KADM5_ADMIN_SERVICE)) != 0)
	krb5_errx (contextp, 1, "ticket for strange principal (%s)",
		   server_name);

    free (server_name);

    memset(&realm_params, 0, sizeof(realm_params));

    if(kadm_version == 1) {
	krb5_data params;
	ret = krb5_read_priv_message(contextp, ac, &fd, &params);
	if(ret)
	    krb5_err(contextp, 1, ret, "krb5_read_priv_message");
	_kadm5_unmarshal_params(contextp, &params, &realm_params);
    }

    initial = ticket->ticket.flags.initial;
    ret = krb5_unparse_name(contextp, ticket->client, &client);
    if (ret)
	krb5_err (contextp, 1, ret, "krb5_unparse_name");
    krb5_free_ticket (contextp, ticket);
    ret = kadm5_s_init_with_password_ctx(contextp,
					 client,
					 NULL,
					 KADM5_ADMIN_SERVICE,
					 &realm_params,
					 0, 0,
					 &kadm_handlep);
    if(ret)
	krb5_err (contextp, 1, ret, "kadm5_init_with_password_ctx");
    v5_loop (contextp, ac, initial, kadm_handlep, fd);
}