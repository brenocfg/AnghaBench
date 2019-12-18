#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_57__   TYPE_9__ ;
typedef  struct TYPE_56__   TYPE_8__ ;
typedef  struct TYPE_55__   TYPE_7__ ;
typedef  struct TYPE_54__   TYPE_6__ ;
typedef  struct TYPE_53__   TYPE_5__ ;
typedef  struct TYPE_52__   TYPE_4__ ;
typedef  struct TYPE_51__   TYPE_3__ ;
typedef  struct TYPE_50__   TYPE_32__ ;
typedef  struct TYPE_49__   TYPE_2__ ;
typedef  struct TYPE_48__   TYPE_24__ ;
typedef  struct TYPE_47__   TYPE_22__ ;
typedef  struct TYPE_46__   TYPE_1__ ;
typedef  struct TYPE_45__   TYPE_14__ ;
typedef  struct TYPE_44__   TYPE_12__ ;
typedef  struct TYPE_43__   TYPE_11__ ;
typedef  struct TYPE_42__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
typedef  scalar_t__ krb5_timestamp ;
typedef  void* krb5_principal ;
typedef  int /*<<< orphan*/  krb5_keyblock ;
typedef  int /*<<< orphan*/  krb5_key_usage ;
struct TYPE_54__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
struct TYPE_55__ {TYPE_6__ keyvalue; int /*<<< orphan*/  keytype; } ;
struct TYPE_57__ {scalar_t__ initial; } ;
struct TYPE_42__ {scalar_t__ authtime; scalar_t__* starttime; scalar_t__* renew_till; scalar_t__ endtime; TYPE_7__ key; TYPE_9__ flags; int /*<<< orphan*/ * caddr; scalar_t__ nonce; int /*<<< orphan*/  srealm; int /*<<< orphan*/  sname; } ;
struct TYPE_56__ {int /*<<< orphan*/  ticket; int /*<<< orphan*/  crealm; int /*<<< orphan*/  cname; } ;
struct TYPE_43__ {TYPE_10__ enc_part; TYPE_8__ kdc_rep; } ;
typedef  TYPE_11__ krb5_kdc_rep ;
typedef  int krb5_error_code ;
typedef  int (* krb5_decrypt_proc ) (TYPE_12__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_11__*) ;
struct TYPE_53__ {int /*<<< orphan*/ * data; scalar_t__ length; } ;
struct TYPE_52__ {size_t length; int /*<<< orphan*/  data; } ;
struct TYPE_51__ {int /*<<< orphan*/ * val; int /*<<< orphan*/  len; } ;
struct TYPE_49__ {TYPE_9__ b; } ;
struct TYPE_48__ {int /*<<< orphan*/ * val; scalar_t__ len; } ;
struct TYPE_46__ {scalar_t__ starttime; scalar_t__ renew_till; scalar_t__ authtime; scalar_t__ endtime; } ;
struct TYPE_47__ {int /*<<< orphan*/ * data; scalar_t__ length; } ;
struct TYPE_50__ {TYPE_22__ keyvalue; int /*<<< orphan*/  keytype; } ;
struct TYPE_45__ {void* client; void* server; TYPE_5__ second_ticket; TYPE_4__ ticket; TYPE_3__ authdata; TYPE_2__ flags; TYPE_24__ addresses; TYPE_1__ times; TYPE_32__ session; } ;
typedef  TYPE_14__ krb5_creds ;
typedef  TYPE_12__* krb5_context ;
typedef  int /*<<< orphan*/  krb5_const_pointer ;
typedef  int /*<<< orphan*/  krb5_addresses ;
struct TYPE_44__ {scalar_t__ kdc_sec_offset; scalar_t__ max_skew; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_MALLOC_ENCODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,size_t*,int) ; 
 unsigned int EXTRACT_TICKET_ALLOW_CNAME_MISMATCH ; 
 unsigned int EXTRACT_TICKET_ALLOW_SERVER_MISMATCH ; 
 unsigned int EXTRACT_TICKET_MATCH_REALM ; 
 unsigned int EXTRACT_TICKET_TIMESYNC ; 
 int KRB5KRB_AP_ERR_MODIFIED ; 
 int KRB5KRB_AP_ERR_SKEW ; 
 int /*<<< orphan*/  N_ (char*,char*) ; 
 int /*<<< orphan*/  Ticket ; 
 int _krb5_principalname2krb5_principal (TYPE_12__*,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ abs (scalar_t__) ; 
 int check_client_referral (TYPE_12__*,TYPE_11__*,void*,void*,TYPE_32__*) ; 
 int check_server_referral (TYPE_12__*,TYPE_11__*,unsigned int,void*,void*,TYPE_32__*) ; 
 int decrypt_tkt (TYPE_12__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_11__*) ; 
 int /*<<< orphan*/  krb5_abortx (TYPE_12__*,char*) ; 
 int /*<<< orphan*/  krb5_clear_error_message (TYPE_12__*) ; 
 scalar_t__ krb5_config_get_bool (TYPE_12__*,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_copy_addresses (TYPE_12__*,int /*<<< orphan*/ *,TYPE_24__*) ; 
 int krb5_data_copy (TYPE_22__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_free_principal (TYPE_12__*,void*) ; 
 char* krb5_principal_get_realm (TYPE_12__*,void*) ; 
 int /*<<< orphan*/  krb5_set_error_message (TYPE_12__*,int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  krb5_timeofday (TYPE_12__*,scalar_t__*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 int stub1 (TYPE_12__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_11__*) ; 

int
_krb5_extract_ticket(krb5_context context,
		     krb5_kdc_rep *rep,
		     krb5_creds *creds,
		     krb5_keyblock *key,
		     krb5_const_pointer keyseed,
		     krb5_key_usage key_usage,
		     krb5_addresses *addrs,
		     unsigned nonce,
		     unsigned flags,
		     krb5_decrypt_proc decrypt_proc,
		     krb5_const_pointer decryptarg)
{
    krb5_error_code ret;
    krb5_principal tmp_principal;
    size_t len = 0;
    time_t tmp_time;
    krb5_timestamp sec_now;

    /* decrypt */

    if (decrypt_proc == NULL)
	decrypt_proc = decrypt_tkt;

    ret = (*decrypt_proc)(context, key, key_usage, decryptarg, rep);
    if (ret)
	goto out;

    /* save session key */

    creds->session.keyvalue.length = 0;
    creds->session.keyvalue.data   = NULL;
    creds->session.keytype = rep->enc_part.key.keytype;
    ret = krb5_data_copy (&creds->session.keyvalue,
			  rep->enc_part.key.keyvalue.data,
			  rep->enc_part.key.keyvalue.length);
    if (ret) {
	krb5_clear_error_message(context);
	goto out;
    }

    /* compare client and save */
    ret = _krb5_principalname2krb5_principal (context,
					      &tmp_principal,
					      rep->kdc_rep.cname,
					      rep->kdc_rep.crealm);
    if (ret)
	goto out;

    /* check client referral and save principal */
    /* anonymous here ? */
    if((flags & EXTRACT_TICKET_ALLOW_CNAME_MISMATCH) == 0) {
	ret = check_client_referral(context, rep,
				    creds->client,
				    tmp_principal,
				    &creds->session);
	if (ret) {
	    krb5_free_principal (context, tmp_principal);
	    goto out;
	}
    }
    krb5_free_principal (context, creds->client);
    creds->client = tmp_principal;

    /* check server referral and save principal */
    ret = _krb5_principalname2krb5_principal (context,
					      &tmp_principal,
					      rep->enc_part.sname,
					      rep->enc_part.srealm);
    if (ret)
	goto out;
    if((flags & EXTRACT_TICKET_ALLOW_SERVER_MISMATCH) == 0){
	ret = check_server_referral(context,
				    rep,
				    flags,
				    creds->server,
				    tmp_principal,
				    &creds->session);
	if (ret) {
	    krb5_free_principal (context, tmp_principal);
	    goto out;
	}
    }
    krb5_free_principal(context, creds->server);
    creds->server = tmp_principal;

    /* verify names */
    if(flags & EXTRACT_TICKET_MATCH_REALM){
	const char *srealm = krb5_principal_get_realm(context, creds->server);
	const char *crealm = krb5_principal_get_realm(context, creds->client);

	if (strcmp(rep->enc_part.srealm, srealm) != 0 ||
	    strcmp(rep->enc_part.srealm, crealm) != 0)
	{
	    ret = KRB5KRB_AP_ERR_MODIFIED;
	    krb5_clear_error_message(context);
	    goto out;
	}
    }

    /* compare nonces */

    if (nonce != (unsigned)rep->enc_part.nonce) {
	ret = KRB5KRB_AP_ERR_MODIFIED;
	krb5_set_error_message(context, ret, N_("malloc: out of memory", ""));
	goto out;
    }

    /* set kdc-offset */

    krb5_timeofday (context, &sec_now);
    if (rep->enc_part.flags.initial
	&& (flags & EXTRACT_TICKET_TIMESYNC)
	&& context->kdc_sec_offset == 0
	&& krb5_config_get_bool (context, NULL,
				 "libdefaults",
				 "kdc_timesync",
				 NULL)) {
	context->kdc_sec_offset = rep->enc_part.authtime - sec_now;
	krb5_timeofday (context, &sec_now);
    }

    /* check all times */

    if (rep->enc_part.starttime) {
	tmp_time = *rep->enc_part.starttime;
    } else
	tmp_time = rep->enc_part.authtime;

    if (creds->times.starttime == 0
	&& abs(tmp_time - sec_now) > context->max_skew) {
	ret = KRB5KRB_AP_ERR_SKEW;
	krb5_set_error_message (context, ret,
				N_("time skew (%d) larger than max (%d)", ""),
			       abs(tmp_time - sec_now),
			       (int)context->max_skew);
	goto out;
    }

    if (creds->times.starttime != 0
	&& tmp_time != creds->times.starttime) {
	krb5_clear_error_message (context);
	ret = KRB5KRB_AP_ERR_MODIFIED;
	goto out;
    }

    creds->times.starttime = tmp_time;

    if (rep->enc_part.renew_till) {
	tmp_time = *rep->enc_part.renew_till;
    } else
	tmp_time = 0;

    if (creds->times.renew_till != 0
	&& tmp_time > creds->times.renew_till) {
	krb5_clear_error_message (context);
	ret = KRB5KRB_AP_ERR_MODIFIED;
	goto out;
    }

    creds->times.renew_till = tmp_time;

    creds->times.authtime = rep->enc_part.authtime;

    if (creds->times.endtime != 0
	&& rep->enc_part.endtime > creds->times.endtime) {
	krb5_clear_error_message (context);
	ret = KRB5KRB_AP_ERR_MODIFIED;
	goto out;
    }

    creds->times.endtime  = rep->enc_part.endtime;

    if(rep->enc_part.caddr)
	krb5_copy_addresses (context, rep->enc_part.caddr, &creds->addresses);
    else if(addrs)
	krb5_copy_addresses (context, addrs, &creds->addresses);
    else {
	creds->addresses.len = 0;
	creds->addresses.val = NULL;
    }
    creds->flags.b = rep->enc_part.flags;

    creds->authdata.len = 0;
    creds->authdata.val = NULL;

    /* extract ticket */
    ASN1_MALLOC_ENCODE(Ticket, creds->ticket.data, creds->ticket.length,
		       &rep->kdc_rep.ticket, &len, ret);
    if(ret)
	goto out;
    if (creds->ticket.length != len)
	krb5_abortx(context, "internal error in ASN.1 encoder");
    creds->second_ticket.length = 0;
    creds->second_ticket.data   = NULL;


out:
    memset (rep->enc_part.key.keyvalue.data, 0,
	    rep->enc_part.key.keyvalue.length);
    return ret;
}