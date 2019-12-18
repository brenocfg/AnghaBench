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
typedef  int /*<<< orphan*/  krb5_context ;
typedef  scalar_t__ krb5_boolean ;
typedef  TYPE_1__* gsskrb5_ctx ;
struct TYPE_3__ {int more_flags; int /*<<< orphan*/  target; } ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 int COMPAT_OLD_DES3 ; 
 int COMPAT_OLD_DES3_SELECTED ; 
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 scalar_t__ check_compat (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__*,scalar_t__) ; 

OM_uint32
_gss_DES3_get_mic_compat(OM_uint32 *minor_status,
			 gsskrb5_ctx ctx,
			 krb5_context context)
{
    krb5_boolean use_compat = FALSE;
    OM_uint32 ret;

    if ((ctx->more_flags & COMPAT_OLD_DES3_SELECTED) == 0) {
	ret = check_compat(minor_status, context, ctx->target,
			   "broken_des3_mic", &use_compat, TRUE);
	if (ret)
	    return ret;
	ret = check_compat(minor_status, context, ctx->target,
			   "correct_des3_mic", &use_compat, FALSE);
	if (ret)
	    return ret;

	if (use_compat)
	    ctx->more_flags |= COMPAT_OLD_DES3;
	ctx->more_flags |= COMPAT_OLD_DES3_SELECTED;
    }
    return 0;
}