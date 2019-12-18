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
typedef  size_t uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  lock; TYPE_1__* dlist; scalar_t__ count; } ;
struct octeon_device {TYPE_2__ dispatch; } ;
struct TYPE_3__ {int /*<<< orphan*/  head; scalar_t__ opcode; } ;

/* Variables and functions */
 size_t LIO_DISPATCH_LIST_SIZE ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
lio_init_dispatch_list(struct octeon_device *oct)
{
	uint32_t	i;

	oct->dispatch.count = 0;

	for (i = 0; i < LIO_DISPATCH_LIST_SIZE; i++) {
		oct->dispatch.dlist[i].opcode = 0;
		STAILQ_INIT(&oct->dispatch.dlist[i].head);
	}

	mtx_init(&oct->dispatch.lock, "dispatch_lock", NULL, MTX_DEF);

	return (0);
}