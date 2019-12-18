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
struct _gss_mech_switch {int /*<<< orphan*/  (* gm_process_context_token ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const) ;} ;
struct _gss_context {int /*<<< orphan*/  gc_ctx; struct _gss_mech_switch* gc_mech; } ;
typedef  scalar_t__ gss_ctx_id_t ;
typedef  int /*<<< orphan*/  gss_buffer_t ;
typedef  int /*<<< orphan*/  OM_uint32 ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 

OM_uint32
gss_process_context_token(OM_uint32 *minor_status,
    const gss_ctx_id_t context_handle,
    const gss_buffer_t token_buffer)
{
	struct _gss_context *ctx = (struct _gss_context *) context_handle;
	struct _gss_mech_switch *m = ctx->gc_mech;

	return (m->gm_process_context_token(minor_status, ctx->gc_ctx,
		    token_buffer));
}