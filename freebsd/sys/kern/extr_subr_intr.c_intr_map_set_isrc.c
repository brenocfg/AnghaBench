#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
struct intr_irqsrc {int dummy; } ;
struct TYPE_2__ {struct intr_irqsrc* isrc; } ;

/* Variables and functions */
 TYPE_1__** irq_map ; 
 size_t irq_map_count ; 
 int /*<<< orphan*/  irq_map_lock ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
intr_map_set_isrc(u_int res_id, struct intr_irqsrc *isrc)
{

	mtx_lock(&irq_map_lock);
	if ((res_id >= irq_map_count) || (irq_map[res_id] == NULL)) {
		mtx_unlock(&irq_map_lock);
		return;
	}
	irq_map[res_id]->isrc = isrc;
	mtx_unlock(&irq_map_lock);
}