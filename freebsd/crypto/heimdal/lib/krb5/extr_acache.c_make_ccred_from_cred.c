#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_38__   TYPE_9__ ;
typedef  struct TYPE_37__   TYPE_8__ ;
typedef  struct TYPE_36__   TYPE_7__ ;
typedef  struct TYPE_35__   TYPE_6__ ;
typedef  struct TYPE_34__   TYPE_5__ ;
typedef  struct TYPE_33__   TYPE_4__ ;
typedef  struct TYPE_32__   TYPE_3__ ;
typedef  struct TYPE_31__   TYPE_2__ ;
typedef  struct TYPE_30__   TYPE_1__ ;
typedef  struct TYPE_29__   TYPE_16__ ;
typedef  struct TYPE_28__   TYPE_15__ ;
typedef  struct TYPE_27__   TYPE_14__ ;
typedef  struct TYPE_26__   TYPE_13__ ;
typedef  struct TYPE_25__   TYPE_12__ ;
typedef  struct TYPE_24__   TYPE_11__ ;
typedef  struct TYPE_23__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ krb5_error_code ;
struct TYPE_26__ {scalar_t__ anonymous; scalar_t__ ok_as_delegate; scalar_t__ transited_policy_checked; scalar_t__ hw_authent; scalar_t__ pre_authent; scalar_t__ initial; scalar_t__ renewable; scalar_t__ invalid; scalar_t__ postdated; scalar_t__ may_postdate; scalar_t__ proxy; scalar_t__ proxiable; scalar_t__ forwarded; scalar_t__ forwardable; } ;
struct TYPE_25__ {TYPE_13__ b; } ;
struct TYPE_24__ {int len; TYPE_10__* val; } ;
struct TYPE_37__ {int /*<<< orphan*/  data; int /*<<< orphan*/  length; } ;
struct TYPE_35__ {int /*<<< orphan*/  data; int /*<<< orphan*/  length; } ;
struct TYPE_33__ {int /*<<< orphan*/  renew_till; int /*<<< orphan*/  endtime; int /*<<< orphan*/  starttime; int /*<<< orphan*/  authtime; } ;
struct TYPE_31__ {int /*<<< orphan*/  data; int /*<<< orphan*/  length; } ;
struct TYPE_32__ {TYPE_2__ keyvalue; int /*<<< orphan*/  keytype; } ;
struct TYPE_27__ {TYPE_12__ flags; TYPE_11__ addresses; TYPE_8__ second_ticket; TYPE_6__ ticket; TYPE_4__ times; TYPE_3__ session; int /*<<< orphan*/  server; int /*<<< orphan*/  client; } ;
typedef  TYPE_14__ krb5_creds ;
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_28__ {int length; int /*<<< orphan*/ * data; int /*<<< orphan*/  type; } ;
typedef  TYPE_15__ cc_data ;
struct TYPE_36__ {int /*<<< orphan*/  data; int /*<<< orphan*/  length; } ;
struct TYPE_34__ {int /*<<< orphan*/  data; int /*<<< orphan*/  length; } ;
struct TYPE_30__ {int /*<<< orphan*/  data; int /*<<< orphan*/  length; int /*<<< orphan*/  type; } ;
struct TYPE_29__ {int /*<<< orphan*/  ticket_flags; TYPE_15__** addresses; int /*<<< orphan*/ * authdata; TYPE_7__ second_ticket; TYPE_5__ ticket; int /*<<< orphan*/  renew_till; int /*<<< orphan*/  endtime; int /*<<< orphan*/  starttime; int /*<<< orphan*/  authtime; TYPE_1__ keyblock; int /*<<< orphan*/  server; int /*<<< orphan*/  client; } ;
typedef  TYPE_16__ cc_credentials_v5_t ;
struct TYPE_38__ {int length; int /*<<< orphan*/  data; } ;
struct TYPE_23__ {TYPE_9__ address; int /*<<< orphan*/  addr_type; } ;

/* Variables and functions */
 scalar_t__ ENOMEM ; 
 int /*<<< orphan*/  KRB5_CCAPI_TKT_FLG_ANONYMOUS ; 
 int /*<<< orphan*/  KRB5_CCAPI_TKT_FLG_FORWARDABLE ; 
 int /*<<< orphan*/  KRB5_CCAPI_TKT_FLG_FORWARDED ; 
 int /*<<< orphan*/  KRB5_CCAPI_TKT_FLG_HW_AUTH ; 
 int /*<<< orphan*/  KRB5_CCAPI_TKT_FLG_INITIAL ; 
 int /*<<< orphan*/  KRB5_CCAPI_TKT_FLG_INVALID ; 
 int /*<<< orphan*/  KRB5_CCAPI_TKT_FLG_MAY_POSTDATE ; 
 int /*<<< orphan*/  KRB5_CCAPI_TKT_FLG_OK_AS_DELEGATE ; 
 int /*<<< orphan*/  KRB5_CCAPI_TKT_FLG_POSTDATED ; 
 int /*<<< orphan*/  KRB5_CCAPI_TKT_FLG_PRE_AUTH ; 
 int /*<<< orphan*/  KRB5_CCAPI_TKT_FLG_PROXIABLE ; 
 int /*<<< orphan*/  KRB5_CCAPI_TKT_FLG_PROXY ; 
 int /*<<< orphan*/  KRB5_CCAPI_TKT_FLG_RENEWABLE ; 
 int /*<<< orphan*/  KRB5_CCAPI_TKT_FLG_TRANSIT_POLICY_CHECKED ; 
 TYPE_15__** calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_15__*) ; 
 int /*<<< orphan*/  free_ccred (TYPE_16__*) ; 
 int /*<<< orphan*/  krb5_clear_error_message (int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_unparse_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (TYPE_16__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static krb5_error_code
make_ccred_from_cred(krb5_context context,
		     const krb5_creds *incred,
		     cc_credentials_v5_t *cred)
{
    krb5_error_code ret;
    size_t i;

    memset(cred, 0, sizeof(*cred));

    ret = krb5_unparse_name(context, incred->client, &cred->client);
    if (ret)
	goto fail;

    ret = krb5_unparse_name(context, incred->server, &cred->server);
    if (ret)
	goto fail;

    cred->keyblock.type = incred->session.keytype;
    cred->keyblock.length = incred->session.keyvalue.length;
    cred->keyblock.data = incred->session.keyvalue.data;

    cred->authtime = incred->times.authtime;
    cred->starttime = incred->times.starttime;
    cred->endtime = incred->times.endtime;
    cred->renew_till = incred->times.renew_till;

    cred->ticket.length = incred->ticket.length;
    cred->ticket.data = incred->ticket.data;

    cred->second_ticket.length = incred->second_ticket.length;
    cred->second_ticket.data = incred->second_ticket.data;

    /* XXX this one should also be filled in */
    cred->authdata = NULL;

    cred->addresses = calloc(incred->addresses.len + 1,
			     sizeof(cred->addresses[0]));
    if (cred->addresses == NULL) {

	ret = ENOMEM;
	goto fail;
    }

    for (i = 0; i < incred->addresses.len; i++) {
	cc_data *addr;
	addr = malloc(sizeof(*addr));
	if (addr == NULL) {
	    ret = ENOMEM;
	    goto fail;
	}
	addr->type = incred->addresses.val[i].addr_type;
	addr->length = incred->addresses.val[i].address.length;
	addr->data = malloc(addr->length);
	if (addr->data == NULL) {
	    free(addr);
	    ret = ENOMEM;
	    goto fail;
	}
	memcpy(addr->data, incred->addresses.val[i].address.data,
	       addr->length);
	cred->addresses[i] = addr;
    }
    cred->addresses[i] = NULL;

    cred->ticket_flags = 0;
    if (incred->flags.b.forwardable)
	cred->ticket_flags |= KRB5_CCAPI_TKT_FLG_FORWARDABLE;
    if (incred->flags.b.forwarded)
	cred->ticket_flags |= KRB5_CCAPI_TKT_FLG_FORWARDED;
    if (incred->flags.b.proxiable)
	cred->ticket_flags |= KRB5_CCAPI_TKT_FLG_PROXIABLE;
    if (incred->flags.b.proxy)
	cred->ticket_flags |= KRB5_CCAPI_TKT_FLG_PROXY;
    if (incred->flags.b.may_postdate)
	cred->ticket_flags |= KRB5_CCAPI_TKT_FLG_MAY_POSTDATE;
    if (incred->flags.b.postdated)
	cred->ticket_flags |= KRB5_CCAPI_TKT_FLG_POSTDATED;
    if (incred->flags.b.invalid)
	cred->ticket_flags |= KRB5_CCAPI_TKT_FLG_INVALID;
    if (incred->flags.b.renewable)
	cred->ticket_flags |= KRB5_CCAPI_TKT_FLG_RENEWABLE;
    if (incred->flags.b.initial)
	cred->ticket_flags |= KRB5_CCAPI_TKT_FLG_INITIAL;
    if (incred->flags.b.pre_authent)
	cred->ticket_flags |= KRB5_CCAPI_TKT_FLG_PRE_AUTH;
    if (incred->flags.b.hw_authent)
	cred->ticket_flags |= KRB5_CCAPI_TKT_FLG_HW_AUTH;
    if (incred->flags.b.transited_policy_checked)
	cred->ticket_flags |= KRB5_CCAPI_TKT_FLG_TRANSIT_POLICY_CHECKED;
    if (incred->flags.b.ok_as_delegate)
	cred->ticket_flags |= KRB5_CCAPI_TKT_FLG_OK_AS_DELEGATE;
    if (incred->flags.b.anonymous)
	cred->ticket_flags |= KRB5_CCAPI_TKT_FLG_ANONYMOUS;

    return 0;

fail:
    free_ccred(cred);

    krb5_clear_error_message(context);
    return ret;
}