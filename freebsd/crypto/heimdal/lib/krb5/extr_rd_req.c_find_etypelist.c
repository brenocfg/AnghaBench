#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_16__ {unsigned int len; TYPE_3__* val; } ;
typedef  TYPE_4__ krb5_authdata ;
typedef  TYPE_5__* krb5_auth_context ;
typedef  int /*<<< orphan*/  adIfRelevant ;
struct TYPE_18__ {int /*<<< orphan*/ * val; scalar_t__ len; } ;
struct TYPE_17__ {TYPE_1__* authenticator; } ;
struct TYPE_14__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
struct TYPE_15__ {scalar_t__ ad_type; TYPE_2__ ad_data; } ;
struct TYPE_13__ {TYPE_4__* authorization_data; } ;
typedef  TYPE_6__ EtypeList ;

/* Variables and functions */
 scalar_t__ KRB5_AUTHDATA_GSS_API_ETYPE_NEGOTIATION ; 
 scalar_t__ KRB5_AUTHDATA_IF_RELEVANT ; 
 scalar_t__ decode_AD_IF_RELEVANT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *) ; 
 scalar_t__ decode_EtypeList (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_AD_IF_RELEVANT (TYPE_4__*) ; 
 int /*<<< orphan*/  krb5_clear_error_message (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static krb5_error_code
find_etypelist(krb5_context context,
	       krb5_auth_context auth_context,
	       EtypeList *etypes)
{
    krb5_error_code ret;
    krb5_authdata *ad;
    krb5_authdata adIfRelevant;
    unsigned i;

    memset(&adIfRelevant, 0, sizeof(adIfRelevant));

    etypes->len = 0;
    etypes->val = NULL;

    ad = auth_context->authenticator->authorization_data;
    if (ad == NULL)
	return 0;

    for (i = 0; i < ad->len; i++) {
	if (ad->val[i].ad_type == KRB5_AUTHDATA_IF_RELEVANT) {
	    ret = decode_AD_IF_RELEVANT(ad->val[i].ad_data.data,
					ad->val[i].ad_data.length,
					&adIfRelevant,
					NULL);
	    if (ret)
		return ret;

	    if (adIfRelevant.len == 1 &&
		adIfRelevant.val[0].ad_type ==
			KRB5_AUTHDATA_GSS_API_ETYPE_NEGOTIATION) {
		break;
	    }
	    free_AD_IF_RELEVANT(&adIfRelevant);
	    adIfRelevant.len = 0;
	}
    }

    if (adIfRelevant.len == 0)
	return 0;

    ret = decode_EtypeList(adIfRelevant.val[0].ad_data.data,
			   adIfRelevant.val[0].ad_data.length,
			   etypes,
			   NULL);
    if (ret)
	krb5_clear_error_message(context);

    free_AD_IF_RELEVANT(&adIfRelevant);

    return ret;
}