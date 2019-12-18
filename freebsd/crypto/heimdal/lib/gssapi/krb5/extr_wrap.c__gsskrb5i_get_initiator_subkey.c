#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_keyblock ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  TYPE_1__* gsskrb5_ctx ;
struct TYPE_3__ {int more_flags; int /*<<< orphan*/  auth_context; } ;

/* Variables and functions */
 scalar_t__ GSS_KRB5_S_KG_NO_SUBKEY ; 
 int LOCAL ; 
 scalar_t__ krb5_auth_con_getkey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ krb5_auth_con_getlocalsubkey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ krb5_auth_con_getremotesubkey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

krb5_error_code
_gsskrb5i_get_initiator_subkey(const gsskrb5_ctx ctx,
			       krb5_context context,
			       krb5_keyblock **key)
{
    krb5_error_code ret;
    *key = NULL;

    if (ctx->more_flags & LOCAL) {
	ret = krb5_auth_con_getlocalsubkey(context,
				     ctx->auth_context,
				     key);
    } else {
	ret = krb5_auth_con_getremotesubkey(context,
				      ctx->auth_context,
				      key);
    }
    if (ret == 0 && *key == NULL)
	ret = krb5_auth_con_getkey(context,
				   ctx->auth_context,
				   key);
    if (ret == 0 && *key == NULL) {
	krb5_set_error_message(context, 0, "No initiator subkey available");
	return GSS_KRB5_S_KG_NO_SUBKEY;
    }
    return ret;
}