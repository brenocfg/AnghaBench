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
struct TYPE_3__ {scalar_t__ nlimbo; int /*<<< orphan*/  tctxs; } ;
typedef  TYPE_1__ prof_gctx_t ;

/* Variables and functions */
 scalar_t__ opt_prof_accum ; 
 int /*<<< orphan*/  tctx_tree_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
prof_gctx_should_destroy(prof_gctx_t *gctx) {
	if (opt_prof_accum) {
		return false;
	}
	if (!tctx_tree_empty(&gctx->tctxs)) {
		return false;
	}
	if (gctx->nlimbo != 0) {
		return false;
	}
	return true;
}