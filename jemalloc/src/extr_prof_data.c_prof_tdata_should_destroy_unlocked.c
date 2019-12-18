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
struct TYPE_3__ {int /*<<< orphan*/  bt2tctx; scalar_t__ attached; } ;
typedef  TYPE_1__ prof_tdata_t ;

/* Variables and functions */
 scalar_t__ ckh_count (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
prof_tdata_should_destroy_unlocked(prof_tdata_t *tdata, bool even_if_attached) {
	if (tdata->attached && !even_if_attached) {
		return false;
	}
	if (ckh_count(&tdata->bt2tctx) != 0) {
		return false;
	}
	return true;
}