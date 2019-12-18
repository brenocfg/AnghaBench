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
struct _gss_mech_switch {scalar_t__ (* gm_inquire_sec_context_by_oid ) (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/ *) ;} ;
struct _gss_context {int /*<<< orphan*/  gc_ctx; struct _gss_mech_switch* gc_mech; } ;
typedef  scalar_t__ gss_ctx_id_t ;
typedef  int /*<<< orphan*/  gss_buffer_set_t ;
typedef  int /*<<< orphan*/  gss_OID ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 int /*<<< orphan*/  GSS_C_NO_BUFFER_SET ; 
 scalar_t__ GSS_S_BAD_MECH ; 
 scalar_t__ GSS_S_COMPLETE ; 
 scalar_t__ GSS_S_NO_CONTEXT ; 
 int /*<<< orphan*/  _gss_mg_error (struct _gss_mech_switch*,scalar_t__,scalar_t__) ; 
 scalar_t__ stub1 (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/ *) ; 

OM_uint32
gss_inquire_sec_context_by_oid(OM_uint32 *minor_status,
    const gss_ctx_id_t context_handle,
    const gss_OID desired_object,
    gss_buffer_set_t *result)
{
	OM_uint32 major_status;
	struct _gss_context *ctx = (struct _gss_context *) context_handle;
	struct _gss_mech_switch *m;

	*minor_status = 0;
	*result = GSS_C_NO_BUFFER_SET;
	if (!ctx)
		return (GSS_S_NO_CONTEXT);

	m = ctx->gc_mech;
	if (m->gm_inquire_sec_context_by_oid) {
		major_status = m->gm_inquire_sec_context_by_oid(
			minor_status, ctx->gc_ctx, desired_object, result);
		if (major_status != GSS_S_COMPLETE)
			_gss_mg_error(m, major_status, *minor_status);
	} else {
		major_status = GSS_S_BAD_MECH;
	}

	return (major_status);
}