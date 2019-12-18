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
struct omap_sham_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SHA_REG_IRQSTATUS ; 
 int /*<<< orphan*/  SHA_REG_IRQSTATUS_INPUT_RDY ; 
 int omap_sham_wait (struct omap_sham_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omap_sham_poll_irq_omap4(struct omap_sham_dev *dd)
{
	return omap_sham_wait(dd, SHA_REG_IRQSTATUS,
			      SHA_REG_IRQSTATUS_INPUT_RDY);
}