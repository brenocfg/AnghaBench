#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  TYPE_1__* gsskrb5_ctx ;
struct TYPE_4__ {int more_flags; int /*<<< orphan*/  state; int /*<<< orphan*/  order; int /*<<< orphan*/  auth_context; int /*<<< orphan*/ * ccache; int /*<<< orphan*/ * kcred; scalar_t__ flags; } ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 int CLOSE_CCACHE ; 
 scalar_t__ GSS_S_COMPLETE ; 
 int /*<<< orphan*/  INITIATOR_READY ; 
 int IS_CFX ; 
 int OPEN ; 
 scalar_t__ _gssapi_msg_order_create (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _gssapi_msg_order_f (scalar_t__) ; 
 int /*<<< orphan*/  _gsskrb5i_is_cfx (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_auth_con_getremoteseqnumber (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_cc_close (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_free_creds (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static OM_uint32
gsskrb5_initiator_ready(
	OM_uint32 * minor_status,
	gsskrb5_ctx ctx,
	krb5_context context)
{
    OM_uint32 ret;
    int32_t seq_number;
    int is_cfx = 0;
    OM_uint32 flags = ctx->flags;

    krb5_free_creds(context, ctx->kcred);
    ctx->kcred = NULL;

    if (ctx->more_flags & CLOSE_CCACHE)
	krb5_cc_close(context, ctx->ccache);
    ctx->ccache = NULL;

    krb5_auth_con_getremoteseqnumber (context, ctx->auth_context, &seq_number);

    _gsskrb5i_is_cfx(context, ctx, 0);
    is_cfx = (ctx->more_flags & IS_CFX);

    ret = _gssapi_msg_order_create(minor_status,
				   &ctx->order,
				   _gssapi_msg_order_f(flags),
				   seq_number, 0, is_cfx);
    if (ret) return ret;

    ctx->state	= INITIATOR_READY;
    ctx->more_flags	|= OPEN;

    return GSS_S_COMPLETE;
}