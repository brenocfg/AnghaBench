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
typedef  int /*<<< orphan*/  gss_name_t ;
typedef  int /*<<< orphan*/  gss_ctx_id_t ;
typedef  int /*<<< orphan*/  gss_buffer_desc ;
typedef  int /*<<< orphan*/  gss_OID ;
typedef  int /*<<< orphan*/  OM_uint32 ;

/* Variables and functions */
 int /*<<< orphan*/  GSS_C_INDEFINITE ; 
 int /*<<< orphan*/  GSS_C_NO_BUFFER ; 
 int /*<<< orphan*/  GSS_C_NO_CHANNEL_BINDINGS ; 
 int /*<<< orphan*/  GSS_C_NO_CONTEXT ; 
 int /*<<< orphan*/  GSS_C_NO_CREDENTIAL ; 
 scalar_t__ GSS_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GSS_S_BAD_MECH ; 
 int /*<<< orphan*/  GSS_S_COMPLETE ; 
 int /*<<< orphan*/  gss_delete_sec_context (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gss_init_sec_context (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gss_mg_collect_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gss_release_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static OM_uint32
initiator_approved(gss_name_t target_name, gss_OID mech)
{
    OM_uint32 min_stat, maj_stat;
    gss_ctx_id_t ctx = GSS_C_NO_CONTEXT;
    gss_buffer_desc out;

    maj_stat = gss_init_sec_context(&min_stat,
				    GSS_C_NO_CREDENTIAL,
				    &ctx,
				    target_name,
				    mech,
				    0,
				    GSS_C_INDEFINITE,
				    GSS_C_NO_CHANNEL_BINDINGS,
				    GSS_C_NO_BUFFER,
				    NULL,
				    &out,
				    NULL,
				    NULL);
    if (GSS_ERROR(maj_stat)) {
	gss_mg_collect_error(mech, maj_stat, min_stat);
	return GSS_S_BAD_MECH;
    }
    gss_release_buffer(&min_stat, &out);
    gss_delete_sec_context(&min_stat, &ctx, NULL);

    return GSS_S_COMPLETE;
}