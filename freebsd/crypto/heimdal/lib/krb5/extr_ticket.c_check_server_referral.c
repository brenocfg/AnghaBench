#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_39__   TYPE_9__ ;
typedef  struct TYPE_38__   TYPE_8__ ;
typedef  struct TYPE_37__   TYPE_7__ ;
typedef  struct TYPE_36__   TYPE_6__ ;
typedef  struct TYPE_35__   TYPE_5__ ;
typedef  struct TYPE_34__   TYPE_4__ ;
typedef  struct TYPE_33__   TYPE_3__ ;
typedef  struct TYPE_32__   TYPE_2__ ;
typedef  struct TYPE_31__   TYPE_1__ ;
typedef  struct TYPE_30__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ref ;
typedef  int /*<<< orphan*/  krb5_keyblock ;
struct TYPE_32__ {TYPE_1__* padata; } ;
struct TYPE_36__ {TYPE_2__ kdc_rep; } ;
typedef  TYPE_6__ krb5_kdc_rep ;
typedef  scalar_t__ krb5_error_code ;
struct TYPE_37__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
typedef  TYPE_7__ krb5_data ;
typedef  int /*<<< orphan*/  krb5_crypto ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  TYPE_8__* krb5_const_principal ;
typedef  int /*<<< orphan*/  ed ;
struct TYPE_39__ {char const** referred_realm; scalar_t__ requested_principal_name; } ;
struct TYPE_34__ {char** val; } ;
struct TYPE_35__ {TYPE_4__ name_string; } ;
struct TYPE_38__ {char const* realm; TYPE_5__ name; } ;
struct TYPE_33__ {size_t length; int /*<<< orphan*/  data; } ;
struct TYPE_31__ {int /*<<< orphan*/  len; int /*<<< orphan*/  val; } ;
struct TYPE_30__ {TYPE_3__ padata_value; } ;
typedef  TYPE_9__ PA_ServerReferralData ;
typedef  TYPE_10__ PA_DATA ;
typedef  TYPE_9__ EncryptedData ;

/* Variables and functions */
 unsigned int EXTRACT_TICKET_AS_REQ ; 
 scalar_t__ KRB5KRB_AP_ERR_MODIFIED ; 
 int /*<<< orphan*/  KRB5_KU_PA_SERVER_REFERRAL ; 
 int /*<<< orphan*/  KRB5_PADATA_SERVER_REFERRAL ; 
 int /*<<< orphan*/  N_ (char*,char*) ; 
 scalar_t__ TRUE ; 
 int _krb5_principal_compare_PrincipalName (int /*<<< orphan*/ ,TYPE_8__*,scalar_t__) ; 
 scalar_t__ decode_EncryptedData (int /*<<< orphan*/ ,size_t,TYPE_9__*,size_t*) ; 
 scalar_t__ decode_PA_ServerReferralData (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_9__*,size_t*) ; 
 int /*<<< orphan*/  free_EncryptedData (TYPE_9__*) ; 
 int /*<<< orphan*/  free_PA_ServerReferralData (TYPE_9__*) ; 
 int /*<<< orphan*/  krb5_crypto_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_crypto_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_data_free (TYPE_7__*) ; 
 scalar_t__ krb5_decrypt_EncryptedData (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_9__*,TYPE_7__*) ; 
 TYPE_10__* krb5_find_padata (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ krb5_principal_compare (int /*<<< orphan*/ ,TYPE_8__*,TYPE_8__*) ; 
 scalar_t__ krb5_principal_is_krbtgt (int /*<<< orphan*/ ,TYPE_8__*) ; 
 scalar_t__ krb5_realm_compare (int /*<<< orphan*/ ,TYPE_8__*,TYPE_8__*) ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  memset (TYPE_9__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcmp (char const*,char const*) ; 

__attribute__((used)) static krb5_error_code
check_server_referral(krb5_context context,
		      krb5_kdc_rep *rep,
		      unsigned flags,
		      krb5_const_principal requested,
		      krb5_const_principal returned,
		      krb5_keyblock * key)
{
    krb5_error_code ret;
    PA_ServerReferralData ref;
    krb5_crypto session;
    EncryptedData ed;
    size_t len;
    krb5_data data;
    PA_DATA *pa;
    int i = 0, cmp;

    if (rep->kdc_rep.padata == NULL)
	goto noreferral;

    pa = krb5_find_padata(rep->kdc_rep.padata->val,
			  rep->kdc_rep.padata->len,
			  KRB5_PADATA_SERVER_REFERRAL, &i);
    if (pa == NULL)
	goto noreferral;

    memset(&ed, 0, sizeof(ed));
    memset(&ref, 0, sizeof(ref));

    ret = decode_EncryptedData(pa->padata_value.data,
			       pa->padata_value.length,
			       &ed, &len);
    if (ret)
	return ret;
    if (len != pa->padata_value.length) {
	free_EncryptedData(&ed);
	krb5_set_error_message(context, KRB5KRB_AP_ERR_MODIFIED,
			       N_("Referral EncryptedData wrong for realm %s",
				  "realm"), requested->realm);
	return KRB5KRB_AP_ERR_MODIFIED;
    }

    ret = krb5_crypto_init(context, key, 0, &session);
    if (ret) {
	free_EncryptedData(&ed);
	return ret;
    }

    ret = krb5_decrypt_EncryptedData(context, session,
				     KRB5_KU_PA_SERVER_REFERRAL,
				     &ed, &data);
    free_EncryptedData(&ed);
    krb5_crypto_destroy(context, session);
    if (ret)
	return ret;

    ret = decode_PA_ServerReferralData(data.data, data.length, &ref, &len);
    if (ret) {
	krb5_data_free(&data);
	return ret;
    }
    krb5_data_free(&data);

    if (strcmp(requested->realm, returned->realm) != 0) {
	free_PA_ServerReferralData(&ref);
	krb5_set_error_message(context, KRB5KRB_AP_ERR_MODIFIED,
			       N_("server ref realm mismatch, "
				  "requested realm %s got back %s", ""),
			       requested->realm, returned->realm);
	return KRB5KRB_AP_ERR_MODIFIED;
    }

    if (krb5_principal_is_krbtgt(context, returned)) {
	const char *realm = returned->name.name_string.val[1];

	if (ref.referred_realm == NULL
	    || strcmp(*ref.referred_realm, realm) != 0)
	{
	    free_PA_ServerReferralData(&ref);
	    krb5_set_error_message(context, KRB5KRB_AP_ERR_MODIFIED,
				   N_("tgt returned with wrong ref", ""));
	    return KRB5KRB_AP_ERR_MODIFIED;
	}
    } else if (krb5_principal_compare(context, returned, requested) == 0) {
	free_PA_ServerReferralData(&ref);
	krb5_set_error_message(context, KRB5KRB_AP_ERR_MODIFIED,
			       N_("req princ no same as returned", ""));
	return KRB5KRB_AP_ERR_MODIFIED;
    }

    if (ref.requested_principal_name) {
	cmp = _krb5_principal_compare_PrincipalName(context,
						    requested,
						    ref.requested_principal_name);
	if (!cmp) {
	    free_PA_ServerReferralData(&ref);
	    krb5_set_error_message(context, KRB5KRB_AP_ERR_MODIFIED,
				   N_("referred principal not same "
				      "as requested", ""));
	    return KRB5KRB_AP_ERR_MODIFIED;
	}
    } else if (flags & EXTRACT_TICKET_AS_REQ) {
	free_PA_ServerReferralData(&ref);
	krb5_set_error_message(context, KRB5KRB_AP_ERR_MODIFIED,
			       N_("Requested principal missing on AS-REQ", ""));
	return KRB5KRB_AP_ERR_MODIFIED;
    }

    free_PA_ServerReferralData(&ref);

    return ret;
noreferral:
    /*
     * Expect excact match or that we got a krbtgt
     */
    if (krb5_principal_compare(context, requested, returned) != TRUE &&
	(krb5_realm_compare(context, requested, returned) != TRUE &&
	 krb5_principal_is_krbtgt(context, returned) != TRUE))
    {
	krb5_set_error_message(context, KRB5KRB_AP_ERR_MODIFIED,
			       N_("Not same server principal returned "
				  "as requested", ""));
	return KRB5KRB_AP_ERR_MODIFIED;
    }
    return 0;
}