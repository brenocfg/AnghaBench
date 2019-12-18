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
struct test_sglist {unsigned int nents; TYPE_2__* sgl_saved; TYPE_1__* sgl; } ;
struct TYPE_4__ {scalar_t__ page_link; scalar_t__ offset; scalar_t__ length; } ;
struct TYPE_3__ {scalar_t__ page_link; scalar_t__ offset; scalar_t__ length; } ;

/* Variables and functions */

__attribute__((used)) static bool is_test_sglist_corrupted(const struct test_sglist *tsgl)
{
	unsigned int i;

	for (i = 0; i < tsgl->nents; i++) {
		if (tsgl->sgl[i].page_link != tsgl->sgl_saved[i].page_link)
			return true;
		if (tsgl->sgl[i].offset != tsgl->sgl_saved[i].offset)
			return true;
		if (tsgl->sgl[i].length != tsgl->sgl_saved[i].length)
			return true;
	}
	return false;
}