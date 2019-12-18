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
struct intr_irqsrc {int /*<<< orphan*/  isrc_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PIC_PRE_ITHREAD (int /*<<< orphan*/ ,struct intr_irqsrc*) ; 

__attribute__((used)) static void
intr_isrc_pre_ithread(void *arg)
{
	struct intr_irqsrc *isrc = arg;

	PIC_PRE_ITHREAD(isrc->isrc_dev, isrc);
}