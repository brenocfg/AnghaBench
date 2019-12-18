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
struct intr_irqsrc {int isrc_flags; } ;

/* Variables and functions */
 int INTR_ISRCF_IPI ; 
 int isrc_free_irq (struct intr_irqsrc*) ; 
 int /*<<< orphan*/  isrc_release_counters (struct intr_irqsrc*) ; 
 int /*<<< orphan*/  isrc_table_lock ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

int
intr_isrc_deregister(struct intr_irqsrc *isrc)
{
	int error;

	mtx_lock(&isrc_table_lock);
	if ((isrc->isrc_flags & INTR_ISRCF_IPI) == 0)
		isrc_release_counters(isrc);
	error = isrc_free_irq(isrc);
	mtx_unlock(&isrc_table_lock);
	return (error);
}