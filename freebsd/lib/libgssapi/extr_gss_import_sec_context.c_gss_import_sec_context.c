#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct _gss_mech_switch {scalar_t__ (* gm_import_sec_context ) (scalar_t__*,TYPE_2__*,int /*<<< orphan*/ *) ;} ;
struct _gss_context {int /*<<< orphan*/  gc_ctx; struct _gss_mech_switch* gc_mech; } ;
typedef  scalar_t__ gss_ctx_id_t ;
typedef  TYPE_1__* gss_buffer_t ;
struct TYPE_8__ {size_t length; unsigned char* value; } ;
typedef  TYPE_2__ gss_buffer_desc ;
struct TYPE_9__ {unsigned char length; unsigned char* elements; } ;
typedef  TYPE_3__ gss_OID_desc ;
struct TYPE_7__ {unsigned char* value; size_t length; } ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 scalar_t__ ENOMEM ; 
 scalar_t__ GSS_C_NO_CONTEXT ; 
 scalar_t__ GSS_S_COMPLETE ; 
 scalar_t__ GSS_S_DEFECTIVE_TOKEN ; 
 scalar_t__ GSS_S_FAILURE ; 
 struct _gss_mech_switch* _gss_find_mech_switch (TYPE_3__*) ; 
 int /*<<< orphan*/  _gss_mg_error (struct _gss_mech_switch*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  free (struct _gss_context*) ; 
 struct _gss_context* malloc (int) ; 
 scalar_t__ stub1 (scalar_t__*,TYPE_2__*,int /*<<< orphan*/ *) ; 

OM_uint32
gss_import_sec_context(OM_uint32 *minor_status,
    const gss_buffer_t interprocess_token,
    gss_ctx_id_t *context_handle)
{
	OM_uint32 major_status;
	struct _gss_mech_switch *m;
	struct _gss_context *ctx;
	gss_OID_desc mech_oid;
	gss_buffer_desc buf;
	unsigned char *p;
	size_t len;

	*minor_status = 0;
	*context_handle = GSS_C_NO_CONTEXT;

	/*
	 * We added an oid to the front of the token in
	 * gss_export_sec_context.
	 */
	p = interprocess_token->value;
	len = interprocess_token->length;
	if (len < 2)
		return (GSS_S_DEFECTIVE_TOKEN);
	mech_oid.length = (p[0] << 8) | p[1];
	if (len < mech_oid.length + 2)
		return (GSS_S_DEFECTIVE_TOKEN);
	mech_oid.elements = p + 2;
	buf.length = len - 2 - mech_oid.length;
	buf.value = p + 2 + mech_oid.length;
	
	m = _gss_find_mech_switch(&mech_oid);
	if (!m)
		return (GSS_S_DEFECTIVE_TOKEN);

	ctx = malloc(sizeof(struct _gss_context));
	if (!ctx) {
		*minor_status = ENOMEM;
		return (GSS_S_FAILURE);
	}
	ctx->gc_mech = m;
	major_status = m->gm_import_sec_context(minor_status,
	    &buf, &ctx->gc_ctx);
	if (major_status != GSS_S_COMPLETE) {
		_gss_mg_error(m, major_status, *minor_status);
		free(ctx);
	} else {
		*context_handle = (gss_ctx_id_t) ctx;
	}

	return (major_status);
}