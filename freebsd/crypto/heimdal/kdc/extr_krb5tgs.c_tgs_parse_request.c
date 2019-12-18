#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_41__   TYPE_9__ ;
typedef  struct TYPE_40__   TYPE_8__ ;
typedef  struct TYPE_39__   TYPE_7__ ;
typedef  struct TYPE_38__   TYPE_6__ ;
typedef  struct TYPE_37__   TYPE_5__ ;
typedef  struct TYPE_36__   TYPE_4__ ;
typedef  struct TYPE_35__   TYPE_3__ ;
typedef  struct TYPE_34__   TYPE_2__ ;
typedef  struct TYPE_33__   TYPE_25__ ;
typedef  struct TYPE_32__   TYPE_1__ ;
typedef  struct TYPE_31__   TYPE_12__ ;
typedef  struct TYPE_30__   TYPE_11__ ;
typedef  struct TYPE_29__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
struct sockaddr {int dummy; } ;
struct TYPE_34__ {int /*<<< orphan*/  key; } ;
struct TYPE_37__ {TYPE_2__ ticket; } ;
typedef  TYPE_5__ krb5_ticket ;
typedef  int /*<<< orphan*/  krb5_principal ;
typedef  int /*<<< orphan*/  krb5_keyblock ;
typedef  int /*<<< orphan*/  krb5_kdc_configuration ;
typedef  scalar_t__ krb5_flags ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_enctype ;
struct TYPE_38__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
typedef  TYPE_6__ krb5_data ;
typedef  int /*<<< orphan*/  krb5_crypto ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  TYPE_7__* krb5_authenticator ;
typedef  int /*<<< orphan*/ * krb5_auth_context ;
struct TYPE_35__ {int /*<<< orphan*/  etype; int /*<<< orphan*/ * kvno; } ;
struct TYPE_36__ {TYPE_3__ enc_part; int /*<<< orphan*/  realm; int /*<<< orphan*/  sname; } ;
struct TYPE_40__ {TYPE_4__ ticket; } ;
typedef  TYPE_8__ krb5_ap_req ;
struct TYPE_33__ {int /*<<< orphan*/  kvno; } ;
struct TYPE_41__ {TYPE_25__ entry; } ;
typedef  TYPE_9__ hdb_entry_ex ;
typedef  int /*<<< orphan*/  ap_req ;
struct TYPE_39__ {int cusec; int /*<<< orphan*/  ctime; } ;
struct TYPE_32__ {scalar_t__ validate; } ;
struct TYPE_31__ {int /*<<< orphan*/  enc_authorization_data; TYPE_1__ kdc_options; } ;
struct TYPE_30__ {int /*<<< orphan*/  key; } ;
struct TYPE_29__ {int /*<<< orphan*/  padata_value; } ;
typedef  TYPE_10__ PA_DATA ;
typedef  TYPE_11__ Key ;
typedef  TYPE_12__ KDC_REQ_BODY ;
typedef  char AuthorizationData ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC (char*) ; 
 scalar_t__ HDB_ERR_NOT_FOUND_HERE ; 
 int /*<<< orphan*/  HDB_F_GET_KRBTGT ; 
 scalar_t__ KRB5KDC_ERR_POLICY ; 
 scalar_t__ KRB5KRB_AP_ERR_BADKEYVER ; 
 scalar_t__ KRB5KRB_AP_ERR_BAD_INTEGRITY ; 
 scalar_t__ KRB5KRB_AP_ERR_NOT_US ; 
 int /*<<< orphan*/  KRB5_KU_TGS_REQ_AUTH ; 
 unsigned int KRB5_KU_TGS_REQ_AUTH_DAT_SESSION ; 
 unsigned int KRB5_KU_TGS_REQ_AUTH_DAT_SUBKEY ; 
 scalar_t__ KRB5_VERIFY_AP_REQ_IGNORE_INVALID ; 
 scalar_t__ _kdc_db_fetch (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_9__**) ; 
 int /*<<< orphan*/  _krb5_principalname2krb5_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ decode_AuthorizationData (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  free_AP_REQ (TYPE_8__*) ; 
 int /*<<< orphan*/  get_krbtgt_realm (int /*<<< orphan*/ *) ; 
 scalar_t__ hdb_enctype2key (int /*<<< orphan*/ ,TYPE_25__*,int /*<<< orphan*/ ,TYPE_11__**) ; 
 int /*<<< orphan*/  kdc_log (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*,...) ; 
 int /*<<< orphan*/  krb5_auth_con_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_auth_con_getauthenticator (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_7__**) ; 
 scalar_t__ krb5_auth_con_getkey (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ krb5_auth_con_getremotesubkey (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  krb5_crypto_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_crypto_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_decode_ap_req (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_8__*) ; 
 scalar_t__ krb5_decrypt_EncryptedData (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  krb5_enctype_to_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  krb5_free_authenticator (int /*<<< orphan*/ ,TYPE_7__**) ; 
 int /*<<< orphan*/  krb5_free_error_message (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  krb5_free_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* krb5_get_error_message (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ krb5_unparse_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 scalar_t__ krb5_verify_ap_req2 (int /*<<< orphan*/ ,int /*<<< orphan*/ **,TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,scalar_t__*,TYPE_5__**,int /*<<< orphan*/ ) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_8__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ tgs_check_authenticator (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_12__*,char const**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static krb5_error_code
tgs_parse_request(krb5_context context,
		  krb5_kdc_configuration *config,
		  KDC_REQ_BODY *b,
		  const PA_DATA *tgs_req,
		  hdb_entry_ex **krbtgt,
		  krb5_enctype *krbtgt_etype,
		  krb5_ticket **ticket,
		  const char **e_text,
		  const char *from,
		  const struct sockaddr *from_addr,
		  time_t **csec,
		  int **cusec,
		  AuthorizationData **auth_data,
		  krb5_keyblock **replykey,
		  int *rk_is_subkey)
{
    static char failed[] = "<unparse_name failed>";
    krb5_ap_req ap_req;
    krb5_error_code ret;
    krb5_principal princ;
    krb5_auth_context ac = NULL;
    krb5_flags ap_req_options;
    krb5_flags verify_ap_req_flags;
    krb5_crypto crypto;
    Key *tkey;
    krb5_keyblock *subkey = NULL;
    unsigned usage;

    *auth_data = NULL;
    *csec  = NULL;
    *cusec = NULL;
    *replykey = NULL;

    memset(&ap_req, 0, sizeof(ap_req));
    ret = krb5_decode_ap_req(context, &tgs_req->padata_value, &ap_req);
    if(ret){
	const char *msg = krb5_get_error_message(context, ret);
	kdc_log(context, config, 0, "Failed to decode AP-REQ: %s", msg);
	krb5_free_error_message(context, msg);
	goto out;
    }

    if(!get_krbtgt_realm(&ap_req.ticket.sname)){
	/* XXX check for ticket.sname == req.sname */
	kdc_log(context, config, 0, "PA-DATA is not a ticket-granting ticket");
	ret = KRB5KDC_ERR_POLICY; /* ? */
	goto out;
    }

    _krb5_principalname2krb5_principal(context,
				       &princ,
				       ap_req.ticket.sname,
				       ap_req.ticket.realm);

    ret = _kdc_db_fetch(context, config, princ, HDB_F_GET_KRBTGT, ap_req.ticket.enc_part.kvno, NULL, krbtgt);

    if(ret == HDB_ERR_NOT_FOUND_HERE) {
	char *p;
	ret = krb5_unparse_name(context, princ, &p);
	if (ret != 0)
	    p = failed;
	krb5_free_principal(context, princ);
	kdc_log(context, config, 5, "Ticket-granting ticket account %s does not have secrets at this KDC, need to proxy", p);
	if (ret == 0)
	    free(p);
	ret = HDB_ERR_NOT_FOUND_HERE;
	goto out;
    } else if(ret){
	const char *msg = krb5_get_error_message(context, ret);
	char *p;
	ret = krb5_unparse_name(context, princ, &p);
	if (ret != 0)
	    p = failed;
	krb5_free_principal(context, princ);
	kdc_log(context, config, 0,
		"Ticket-granting ticket not found in database: %s", msg);
	krb5_free_error_message(context, msg);
	if (ret == 0)
	    free(p);
	ret = KRB5KRB_AP_ERR_NOT_US;
	goto out;
    }

    if(ap_req.ticket.enc_part.kvno &&
       *ap_req.ticket.enc_part.kvno != (*krbtgt)->entry.kvno){
	char *p;

	ret = krb5_unparse_name (context, princ, &p);
	krb5_free_principal(context, princ);
	if (ret != 0)
	    p = failed;
	kdc_log(context, config, 0,
		"Ticket kvno = %d, DB kvno = %d (%s)",
		*ap_req.ticket.enc_part.kvno,
		(*krbtgt)->entry.kvno,
		p);
	if (ret == 0)
	    free (p);
	ret = KRB5KRB_AP_ERR_BADKEYVER;
	goto out;
    }

    *krbtgt_etype = ap_req.ticket.enc_part.etype;

    ret = hdb_enctype2key(context, &(*krbtgt)->entry,
			  ap_req.ticket.enc_part.etype, &tkey);
    if(ret){
	char *str = NULL, *p = NULL;

	krb5_enctype_to_string(context, ap_req.ticket.enc_part.etype, &str);
	krb5_unparse_name(context, princ, &p);
 	kdc_log(context, config, 0,
		"No server key with enctype %s found for %s",
		str ? str : "<unknown enctype>",
		p ? p : "<unparse_name failed>");
	free(str);
	free(p);
	ret = KRB5KRB_AP_ERR_BADKEYVER;
	goto out;
    }

    if (b->kdc_options.validate)
	verify_ap_req_flags = KRB5_VERIFY_AP_REQ_IGNORE_INVALID;
    else
	verify_ap_req_flags = 0;

    ret = krb5_verify_ap_req2(context,
			      &ac,
			      &ap_req,
			      princ,
			      &tkey->key,
			      verify_ap_req_flags,
			      &ap_req_options,
			      ticket,
			      KRB5_KU_TGS_REQ_AUTH);

    krb5_free_principal(context, princ);
    if(ret) {
	const char *msg = krb5_get_error_message(context, ret);
	kdc_log(context, config, 0, "Failed to verify AP-REQ: %s", msg);
	krb5_free_error_message(context, msg);
	goto out;
    }

    {
	krb5_authenticator auth;

	ret = krb5_auth_con_getauthenticator(context, ac, &auth);
	if (ret == 0) {
	    *csec   = malloc(sizeof(**csec));
	    if (*csec == NULL) {
		krb5_free_authenticator(context, &auth);
		kdc_log(context, config, 0, "malloc failed");
		goto out;
	    }
	    **csec  = auth->ctime;
	    *cusec  = malloc(sizeof(**cusec));
	    if (*cusec == NULL) {
		krb5_free_authenticator(context, &auth);
		kdc_log(context, config, 0, "malloc failed");
		goto out;
	    }
	    **cusec  = auth->cusec;
	    krb5_free_authenticator(context, &auth);
	}
    }

    ret = tgs_check_authenticator(context, config,
				  ac, b, e_text, &(*ticket)->ticket.key);
    if (ret) {
	krb5_auth_con_free(context, ac);
	goto out;
    }

    usage = KRB5_KU_TGS_REQ_AUTH_DAT_SUBKEY;
    *rk_is_subkey = 1;

    ret = krb5_auth_con_getremotesubkey(context, ac, &subkey);
    if(ret){
	const char *msg = krb5_get_error_message(context, ret);
	krb5_auth_con_free(context, ac);
	kdc_log(context, config, 0, "Failed to get remote subkey: %s", msg);
	krb5_free_error_message(context, msg);
	goto out;
    }
    if(subkey == NULL){
	usage = KRB5_KU_TGS_REQ_AUTH_DAT_SESSION;
	*rk_is_subkey = 0;

	ret = krb5_auth_con_getkey(context, ac, &subkey);
	if(ret) {
	    const char *msg = krb5_get_error_message(context, ret);
	    krb5_auth_con_free(context, ac);
	    kdc_log(context, config, 0, "Failed to get session key: %s", msg);
	    krb5_free_error_message(context, msg);
	    goto out;
	}
    }
    if(subkey == NULL){
	krb5_auth_con_free(context, ac);
	kdc_log(context, config, 0,
		"Failed to get key for enc-authorization-data");
	ret = KRB5KRB_AP_ERR_BAD_INTEGRITY; /* ? */
	goto out;
    }

    *replykey = subkey;

    if (b->enc_authorization_data) {
	krb5_data ad;

	ret = krb5_crypto_init(context, subkey, 0, &crypto);
	if (ret) {
	    const char *msg = krb5_get_error_message(context, ret);
	    krb5_auth_con_free(context, ac);
	    kdc_log(context, config, 0, "krb5_crypto_init failed: %s", msg);
	    krb5_free_error_message(context, msg);
	    goto out;
	}
	ret = krb5_decrypt_EncryptedData (context,
					  crypto,
					  usage,
					  b->enc_authorization_data,
					  &ad);
	krb5_crypto_destroy(context, crypto);
	if(ret){
	    krb5_auth_con_free(context, ac);
	    kdc_log(context, config, 0,
		    "Failed to decrypt enc-authorization-data");
	    ret = KRB5KRB_AP_ERR_BAD_INTEGRITY; /* ? */
	    goto out;
	}
	ALLOC(*auth_data);
	if (*auth_data == NULL) {
	    krb5_auth_con_free(context, ac);
	    ret = KRB5KRB_AP_ERR_BAD_INTEGRITY; /* ? */
	    goto out;
	}
	ret = decode_AuthorizationData(ad.data, ad.length, *auth_data, NULL);
	if(ret){
	    krb5_auth_con_free(context, ac);
	    free(*auth_data);
	    *auth_data = NULL;
	    kdc_log(context, config, 0, "Failed to decode authorization data");
	    ret = KRB5KRB_AP_ERR_BAD_INTEGRITY; /* ? */
	    goto out;
	}
    }

    krb5_auth_con_free(context, ac);

out:
    free_AP_REQ(&ap_req);

    return ret;
}