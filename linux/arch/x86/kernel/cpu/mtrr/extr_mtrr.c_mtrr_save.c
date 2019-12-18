#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  (* get ) (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  ltype; int /*<<< orphan*/  lsize; int /*<<< orphan*/  lbase; } ;

/* Variables and functions */
 TYPE_2__* mtrr_if ; 
 TYPE_1__* mtrr_value ; 
 int num_var_ranges ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mtrr_save(void)
{
	int i;

	for (i = 0; i < num_var_ranges; i++) {
		mtrr_if->get(i, &mtrr_value[i].lbase,
				&mtrr_value[i].lsize,
				&mtrr_value[i].ltype);
	}
	return 0;
}