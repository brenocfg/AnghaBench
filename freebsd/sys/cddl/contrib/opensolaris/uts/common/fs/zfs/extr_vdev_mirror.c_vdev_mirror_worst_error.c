#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int mm_children; TYPE_2__* mm_child; } ;
typedef  TYPE_1__ mirror_map_t ;
struct TYPE_5__ {int mc_speculative; int /*<<< orphan*/  mc_error; } ;
typedef  TYPE_2__ mirror_child_t ;

/* Variables and functions */
 int zio_worst_error (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vdev_mirror_worst_error(mirror_map_t *mm)
{
	int error[2] = { 0, 0 };

	for (int c = 0; c < mm->mm_children; c++) {
		mirror_child_t *mc = &mm->mm_child[c];
		int s = mc->mc_speculative;
		error[s] = zio_worst_error(error[s], mc->mc_error);
	}

	return (error[0] ? error[0] : error[1]);
}