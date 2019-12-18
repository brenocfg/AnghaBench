#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct busdma_bufzone {int /*<<< orphan*/  umazone; } ;
typedef  TYPE_1__* busdma_bufalloc_t ;
struct TYPE_4__ {int num_zones; struct busdma_bufzone* buf_zones; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  free (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uma_zdestroy (int /*<<< orphan*/ ) ; 

void 
busdma_bufalloc_destroy(busdma_bufalloc_t ba)
{
	struct busdma_bufzone *bz;
	int i;

	if (ba == NULL)
		return;

	for (i = 0, bz = ba->buf_zones; i < ba->num_zones; ++i, ++bz) {
		uma_zdestroy(bz->umazone);
	}

	free(ba, M_DEVBUF);
}