#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct _gss_mech_switch {scalar_t__ (* gm_get_mic ) (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ;} ;
struct _gss_context {int /*<<< orphan*/  gc_ctx; struct _gss_mech_switch* gc_mech; } ;
typedef  int /*<<< orphan*/  gss_qop_t ;
typedef  scalar_t__ gss_ctx_id_t ;
typedef  int /*<<< orphan*/  gss_buffer_t ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 scalar_t__ GSS_S_NO_CONTEXT ; 
 int /*<<< orphan*/  _gss_buffer_zero (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 

OM_uint32
gss_get_mic(OM_uint32 *minor_status,
    const gss_ctx_id_t context_handle,
    gss_qop_t qop_req,
    const gss_buffer_t message_buffer,
    gss_buffer_t message_token)
{
	struct _gss_context *ctx = (struct _gss_context *) context_handle;
	struct _gss_mech_switch *m;

	_gss_buffer_zero(message_token);
	if (ctx == NULL) {
		*minor_status = 0;
		return (GSS_S_NO_CONTEXT);
	}
	m = ctx->gc_mech;

	return (m->gm_get_mic(minor_status, ctx->gc_ctx, qop_req,
		    message_buffer, message_token));
}