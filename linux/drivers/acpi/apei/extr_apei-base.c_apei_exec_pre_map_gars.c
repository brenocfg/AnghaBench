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
struct apei_exec_context {int entries; } ;

/* Variables and functions */
 int apei_exec_for_each_entry (struct apei_exec_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  apei_exec_post_unmap_gars (struct apei_exec_context*) ; 
 int /*<<< orphan*/  memcpy (struct apei_exec_context*,struct apei_exec_context*,int) ; 
 int /*<<< orphan*/  pre_map_gar_callback ; 

int apei_exec_pre_map_gars(struct apei_exec_context *ctx)
{
	int rc, end;

	rc = apei_exec_for_each_entry(ctx, pre_map_gar_callback,
				      NULL, &end);
	if (rc) {
		struct apei_exec_context ctx_unmap;
		memcpy(&ctx_unmap, ctx, sizeof(*ctx));
		ctx_unmap.entries = end;
		apei_exec_post_unmap_gars(&ctx_unmap);
	}

	return rc;
}