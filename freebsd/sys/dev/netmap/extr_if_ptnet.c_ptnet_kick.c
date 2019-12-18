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
struct TYPE_3__ {int /*<<< orphan*/  kicks; } ;
struct ptnet_queue {int /*<<< orphan*/  kick; TYPE_2__* sc; TYPE_1__ stats; } ;
struct TYPE_4__ {int /*<<< orphan*/  iomem; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ptnet_kick(struct ptnet_queue *pq)
{
#ifdef PTNETMAP_STATS
	pq->stats.kicks ++;
#endif /* PTNETMAP_STATS */
	bus_write_4(pq->sc->iomem, pq->kick, 0);
}