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
typedef  size_t u_int ;
struct intr_irqsrc {size_t isrc_index; int /*<<< orphan*/ * isrc_count; } ;

/* Variables and functions */
 size_t atomic_fetchadd_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * intrcnt ; 
 int /*<<< orphan*/  intrcnt_index ; 
 int /*<<< orphan*/  isrc_update_name (struct intr_irqsrc*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
isrc_setup_counters(struct intr_irqsrc *isrc)
{
	u_int index;

	/*
	 *  XXX - it does not work well with removable controllers and
	 *        interrupt sources !!!
	 */
	index = atomic_fetchadd_int(&intrcnt_index, 2);
	isrc->isrc_index = index;
	isrc->isrc_count = &intrcnt[index];
	isrc_update_name(isrc, NULL);
}