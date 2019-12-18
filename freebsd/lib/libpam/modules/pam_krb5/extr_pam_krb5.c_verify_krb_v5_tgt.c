#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_principal ;
typedef  int /*<<< orphan*/  krb5_keyblock ;
typedef  int krb5_error_code ;
struct TYPE_5__ {scalar_t__ data; } ;
typedef  TYPE_1__ krb5_data ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  krb5_ccache ;
typedef  int /*<<< orphan*/ * krb5_auth_context ;

/* Variables and functions */
 int BUFSIZ ; 
 int /*<<< orphan*/  KRB5_NT_SRV_HST ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  compat_free_data_contents (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  compat_princ_component (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  krb5_auth_con_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_free_error_message (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  krb5_free_keyblock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_free_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* krb5_get_error_message (int /*<<< orphan*/ ,int) ; 
 int krb5_kt_read_service_key (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int krb5_mk_req (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int krb5_rd_req (int /*<<< orphan*/ ,int /*<<< orphan*/ **,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int krb5_sname_to_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,char*,char const*) ; 

__attribute__((used)) static int
verify_krb_v5_tgt(krb5_context context, krb5_ccache ccache,
    char *pam_service, int debug)
{
	krb5_error_code retval;
	krb5_principal princ;
	krb5_keyblock *keyblock;
	krb5_data packet;
	krb5_auth_context auth_context;
	char phost[BUFSIZ];
	const char *services[3], **service;

	packet.data = 0;

	/* If possible we want to try and verify the ticket we have
	 * received against a keytab.  We will try multiple service
	 * principals, including at least the host principal and the PAM
	 * service principal.  The host principal is preferred because access
	 * to that key is generally sufficient to compromise root, while the
	 * service key for this PAM service may be less carefully guarded.
	 * It is important to check the keytab first before the KDC so we do
	 * not get spoofed by a fake KDC.
	 */
	services[0] = "host";
	services[1] = pam_service;
	services[2] = NULL;
	keyblock = NULL;
	retval = -1;
	for (service = &services[0]; *service != NULL; service++) {
		retval = krb5_sname_to_principal(context, NULL, *service,
		    KRB5_NT_SRV_HST, &princ);
		if (retval != 0) {
			if (debug) {
				const char *msg = krb5_get_error_message(
				    context, retval);
				syslog(LOG_DEBUG,
				    "pam_krb5: verify_krb_v5_tgt(): %s: %s",
				    "krb5_sname_to_principal()", msg);
				krb5_free_error_message(context, msg);
			}
			return -1;
		}

		/* Extract the name directly. */
		strncpy(phost, compat_princ_component(context, princ, 1),
		    BUFSIZ);
		phost[BUFSIZ - 1] = '\0';

		/*
		 * Do we have service/<host> keys?
		 * (use default/configured keytab, kvno IGNORE_VNO to get the
		 * first match, and ignore enctype.)
		 */
		retval = krb5_kt_read_service_key(context, NULL, princ, 0, 0,
		    &keyblock);
		if (retval != 0)
			continue;
		break;
	}
	if (retval != 0) {	/* failed to find key */
		/* Keytab or service key does not exist */
		if (debug) {
			const char *msg = krb5_get_error_message(context,
			    retval);
			syslog(LOG_DEBUG,
			    "pam_krb5: verify_krb_v5_tgt(): %s: %s",
			    "krb5_kt_read_service_key()", msg);
			krb5_free_error_message(context, msg);
		}
		retval = 0;
		goto cleanup;
	}
	if (keyblock)
		krb5_free_keyblock(context, keyblock);

	/* Talk to the kdc and construct the ticket. */
	auth_context = NULL;
	retval = krb5_mk_req(context, &auth_context, 0, *service, phost,
		NULL, ccache, &packet);
	if (auth_context) {
		krb5_auth_con_free(context, auth_context);
		auth_context = NULL;	/* setup for rd_req */
	}
	if (retval) {
		if (debug) {
			const char *msg = krb5_get_error_message(context,
			    retval);
			syslog(LOG_DEBUG,
			    "pam_krb5: verify_krb_v5_tgt(): %s: %s",
			    "krb5_mk_req()", msg);
			krb5_free_error_message(context, msg);
		}
		retval = -1;
		goto cleanup;
	}

	/* Try to use the ticket. */
	retval = krb5_rd_req(context, &auth_context, &packet, princ, NULL,
	    NULL, NULL);
	if (retval) {
		if (debug) {
			const char *msg = krb5_get_error_message(context,
			    retval);
			syslog(LOG_DEBUG,
			    "pam_krb5: verify_krb_v5_tgt(): %s: %s",
			    "krb5_rd_req()", msg);
			krb5_free_error_message(context, msg);
		}
		retval = -1;
	}
	else
		retval = 1;

cleanup:
	if (packet.data)
		compat_free_data_contents(context, &packet);
	krb5_free_principal(context, princ);
	return retval;
}