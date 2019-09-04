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
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int /*<<< orphan*/  OnigRegion ;

/* Variables and functions */
 int /*<<< orphan*/  onig_region_free (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
match_data_free(mrb_state* mrb, void* p) {
  (void)mrb;
  onig_region_free((OnigRegion*)p, 1);
}