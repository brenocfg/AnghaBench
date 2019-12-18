#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_data ;
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_9__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
struct TYPE_8__ {int len; TYPE_1__* val; } ;
struct TYPE_7__ {scalar_t__ ad_type; TYPE_5__ ad_data; } ;
typedef  TYPE_2__ AuthorizationData ;

/* Variables and functions */
 scalar_t__ KRB5KDC_ERR_PADATA_TYPE_NOSUPP ; 
 scalar_t__ KRB5_AUTHDATA_IF_RELEVANT ; 
 scalar_t__ KRB5_AUTHDATA_SIGNTICKET ; 
 scalar_t__ decode_AuthorizationData (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ der_copy_octet_string (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_AuthorizationData (TYPE_2__*) ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,scalar_t__,char*,scalar_t__) ; 

__attribute__((used)) static krb5_error_code
find_KRB5SignedPath(krb5_context context,
		    const AuthorizationData *ad,
		    krb5_data *data)
{
    AuthorizationData child;
    krb5_error_code ret;
    int pos;

    if (ad == NULL || ad->len == 0)
	return KRB5KDC_ERR_PADATA_TYPE_NOSUPP;

    pos = ad->len - 1;

    if (ad->val[pos].ad_type != KRB5_AUTHDATA_IF_RELEVANT)
	return KRB5KDC_ERR_PADATA_TYPE_NOSUPP;

    ret = decode_AuthorizationData(ad->val[pos].ad_data.data,
				   ad->val[pos].ad_data.length,
				   &child,
				   NULL);
    if (ret) {
	krb5_set_error_message(context, ret, "Failed to decode "
			       "IF_RELEVANT with %d", ret);
	return ret;
    }

    if (child.len != 1) {
	free_AuthorizationData(&child);
	return KRB5KDC_ERR_PADATA_TYPE_NOSUPP;
    }

    if (child.val[0].ad_type != KRB5_AUTHDATA_SIGNTICKET) {
	free_AuthorizationData(&child);
	return KRB5KDC_ERR_PADATA_TYPE_NOSUPP;
    }

    if (data)
	ret = der_copy_octet_string(&child.val[0].ad_data, data);
    free_AuthorizationData(&child);
    return ret;
}