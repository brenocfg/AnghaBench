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
struct _gss_mech_switch {scalar_t__ (* gm_verify_mic ) (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/  const,scalar_t__*) ;} ;
struct _gss_context {int /*<<< orphan*/  gc_ctx; struct _gss_mech_switch* gc_mech; } ;
typedef  scalar_t__ gss_qop_t ;
typedef  scalar_t__ gss_ctx_id_t ;
typedef  int /*<<< orphan*/  gss_buffer_t ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 scalar_t__ GSS_S_NO_CONTEXT ; 
 scalar_t__ stub1 (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/  const,scalar_t__*) ; 

OM_uint32
gss_verify_mic(OM_uint32 *minor_status,
    const gss_ctx_id_t context_handle,
    const gss_buffer_t message_buffer,
    const gss_buffer_t token_buffer,
    gss_qop_t *qop_state)
{
	struct _gss_context *ctx = (struct _gss_context *) context_handle;
	struct _gss_mech_switch *m;

	if (qop_state)
		*qop_state = 0;
	if (ctx == NULL) {
		*minor_status = 0;
		return (GSS_S_NO_CONTEXT);
	}
	m = ctx->gc_mech;

	return (m->gm_verify_mic(minor_status, ctx->gc_ctx,
		    message_buffer, token_buffer, qop_state));
}