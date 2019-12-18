#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  TYPE_2__* gsskrb5_ctx ;
typedef  int /*<<< orphan*/  gss_cred_id_t ;
struct TYPE_6__ {scalar_t__ length; } ;
struct TYPE_7__ {int more_flags; int flags; int /*<<< orphan*/  state; TYPE_1__ fwd_data; int /*<<< orphan*/  auth_context; int /*<<< orphan*/  order; } ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 int /*<<< orphan*/  ACCEPTOR_READY ; 
 int GSS_C_DELEG_FLAG ; 
 int GSS_C_MUTUAL_FLAG ; 
 scalar_t__ GSS_S_COMPLETE ; 
 int IS_CFX ; 
 int OPEN ; 
 scalar_t__ _gssapi_msg_order_create (scalar_t__*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ _gssapi_msg_order_f (int) ; 
 int /*<<< orphan*/  _gsskrb5i_is_cfx (int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 scalar_t__ gsskrb5_accept_delegated_token (scalar_t__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_auth_con_getremoteseqnumber (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_auth_con_setlocalseqnumber (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static OM_uint32
gsskrb5_acceptor_ready(OM_uint32 * minor_status,
		       gsskrb5_ctx ctx,
		       krb5_context context,
		       gss_cred_id_t *delegated_cred_handle)
{
    OM_uint32 ret;
    int32_t seq_number;
    int is_cfx = 0;

    krb5_auth_con_getremoteseqnumber (context,
				      ctx->auth_context,
				      &seq_number);

    _gsskrb5i_is_cfx(context, ctx, 1);
    is_cfx = (ctx->more_flags & IS_CFX);

    ret = _gssapi_msg_order_create(minor_status,
				   &ctx->order,
				   _gssapi_msg_order_f(ctx->flags),
				   seq_number, 0, is_cfx);
    if (ret)
	return ret;

    /*
     * If requested, set local sequence num to remote sequence if this
     * isn't a mutual authentication context
     */
    if (!(ctx->flags & GSS_C_MUTUAL_FLAG) && _gssapi_msg_order_f(ctx->flags)) {
	krb5_auth_con_setlocalseqnumber(context,
					ctx->auth_context,
					seq_number);
    }

    /*
     * We should handle the delegation ticket, in case it's there
     */
    if (ctx->fwd_data.length > 0 && (ctx->flags & GSS_C_DELEG_FLAG)) {
	ret = gsskrb5_accept_delegated_token(minor_status,
					     ctx,
					     context,
					     delegated_cred_handle);
	if (ret)
	    return ret;
    } else {
	/* Well, looks like it wasn't there after all */
	ctx->flags &= ~GSS_C_DELEG_FLAG;
    }

    ctx->state = ACCEPTOR_READY;
    ctx->more_flags |= OPEN;

    return GSS_S_COMPLETE;
}