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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRIZEPS4_MMC_IRQ ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void trizeps4_mci_exit(struct device *dev, void *data)
{
	free_irq(TRIZEPS4_MMC_IRQ, data);
}