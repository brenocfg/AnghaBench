#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* krb5_principal ;
struct TYPE_17__ {int forwarded; int /*<<< orphan*/  forwardable; } ;
struct TYPE_19__ {scalar_t__ i; TYPE_2__ b; } ;
typedef  TYPE_4__ krb5_kdc_flags ;
typedef  scalar_t__ krb5_error_code ;
struct TYPE_20__ {size_t length; void* data; } ;
typedef  TYPE_5__ krb5_data ;
struct TYPE_16__ {scalar_t__ endtime; } ;
struct TYPE_21__ {TYPE_1__ times; int /*<<< orphan*/  server; TYPE_3__* client; } ;
typedef  TYPE_6__ krb5_creds ;
typedef  int /*<<< orphan*/  krb5_ccache ;
typedef  int /*<<< orphan*/  krb5_auth_context ;
typedef  int /*<<< orphan*/  creds ;
struct TYPE_18__ {int /*<<< orphan*/  realm; } ;

/* Variables and functions */
 int AP_OPTS_MUTUAL_REQUIRED ; 
 int AP_OPTS_USE_SUBKEY ; 
 int /*<<< orphan*/  KF_VERSION_1 ; 
 int /*<<< orphan*/  KRB5_NT_SRV_HST ; 
 int /*<<< orphan*/  KRB5_TGS_NAME ; 
 char* ccache_name ; 
 int /*<<< orphan*/  context ; 
 int /*<<< orphan*/  forwardable ; 
 int /*<<< orphan*/  krb5_auth_con_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_auth_con_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_auth_con_setaddrs_from_fd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ krb5_cc_default (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_cc_get_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__**) ; 
 int /*<<< orphan*/  krb5_data_free (TYPE_5__*) ; 
 scalar_t__ krb5_get_forwarded_creds (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,char const*,TYPE_6__*,TYPE_5__*) ; 
 scalar_t__ krb5_make_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_read_priv_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,TYPE_5__*) ; 
 scalar_t__ krb5_sendauth (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_sname_to_principal (int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ ,TYPE_3__**) ; 
 int /*<<< orphan*/  krb5_warn (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int /*<<< orphan*/  krb5_warnx (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ krb5_write_priv_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,TYPE_5__*) ; 
 int /*<<< orphan*/  memcpy (char*,void*,size_t) ; 
 int /*<<< orphan*/  memset (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 char* remote_name ; 
 int strcmp (char*,char*) ; 
 void* strlen (char*) ; 

__attribute__((used)) static int
proto (int sock, const char *hostname, const char *service,
       char *message, size_t len)
{
    krb5_auth_context auth_context;
    krb5_error_code status;
    krb5_principal server;
    krb5_data data;
    krb5_data data_send;

    krb5_ccache     ccache;
    krb5_creds      creds;
    krb5_kdc_flags  flags;
    krb5_principal  principal;

    status = krb5_auth_con_init (context, &auth_context);
    if (status) {
	krb5_warn (context, status, "krb5_auth_con_init");
	return 1;
    }

    status = krb5_auth_con_setaddrs_from_fd (context,
					     auth_context,
					     &sock);
    if (status) {
	krb5_auth_con_free(context, auth_context);
	krb5_warn (context, status, "krb5_auth_con_setaddr");
	return 1;
    }

    status = krb5_sname_to_principal (context,
				      hostname,
				      service,
				      KRB5_NT_SRV_HST,
				      &server);
    if (status) {
	krb5_auth_con_free(context, auth_context);
	krb5_warn (context, status, "krb5_sname_to_principal");
	return 1;
    }

    status = krb5_sendauth (context,
			    &auth_context,
			    &sock,
			    KF_VERSION_1,
			    NULL,
			    server,
			    AP_OPTS_MUTUAL_REQUIRED | AP_OPTS_USE_SUBKEY,
			    NULL,
			    NULL,
			    NULL,
			    NULL,
			    NULL,
			    NULL);
    if (status) {
	krb5_auth_con_free(context, auth_context);
	krb5_warn(context, status, "krb5_sendauth");
	return 1;
    }

    if (ccache_name == NULL)
	ccache_name = "";

    data_send.data   = (void *)remote_name;
    data_send.length = strlen(remote_name) + 1;
    status = krb5_write_priv_message(context, auth_context, &sock, &data_send);
    if (status) {
	krb5_auth_con_free(context, auth_context);
	krb5_warn (context, status, "krb5_write_message");
	return 1;
    }
    data_send.data   = (void *)ccache_name;
    data_send.length = strlen(ccache_name)+1;
    status = krb5_write_priv_message(context, auth_context, &sock, &data_send);
    if (status) {
	krb5_auth_con_free(context, auth_context);
	krb5_warn (context, status, "krb5_write_message");
	return 1;
    }

    memset (&creds, 0, sizeof(creds));

    status = krb5_cc_default (context, &ccache);
    if (status) {
	krb5_auth_con_free(context, auth_context);
	krb5_warn (context, status, "krb5_cc_default");
	return 1;
    }

    status = krb5_cc_get_principal (context, ccache, &principal);
    if (status) {
	krb5_auth_con_free(context, auth_context);
	krb5_warn (context, status, "krb5_cc_get_principal");
	return 1;
    }

    creds.client = principal;

    status = krb5_make_principal (context,
				  &creds.server,
				  principal->realm,
				  KRB5_TGS_NAME,
				  principal->realm,
				  NULL);

    if (status) {
	krb5_auth_con_free(context, auth_context);
	krb5_warn (context, status, "krb5_make_principal");
	return 1;
    }

    creds.times.endtime = 0;

    flags.i = 0;
    flags.b.forwarded   = 1;
    flags.b.forwardable = forwardable;

    status = krb5_get_forwarded_creds (context,
				       auth_context,
				       ccache,
				       flags.i,
				       hostname,
				       &creds,
				       &data);
    if (status) {
	krb5_auth_con_free(context, auth_context);
	krb5_warn (context, status, "krb5_get_forwarded_creds");
	return 1;
    }

    status = krb5_write_priv_message(context, auth_context, &sock, &data);

    if (status) {
	krb5_auth_con_free(context, auth_context);
	krb5_warn (context, status, "krb5_mk_priv");
	return 1;
    }

    krb5_data_free (&data);

    status = krb5_read_priv_message(context, auth_context, &sock, &data);
    krb5_auth_con_free(context, auth_context);
    if (status) {
	krb5_warn (context, status, "krb5_mk_priv");
	return 1;
    }
    if(data.length >= len) {
	krb5_warnx (context, "returned string is too long, truncating");
	memcpy(message, data.data, len);
	message[len - 1] = '\0';
    } else {
	memcpy(message, data.data, data.length);
	message[data.length] = '\0';
    }
    krb5_data_free (&data);

    return(strcmp(message, "ok"));
}