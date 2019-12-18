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
struct sh_dmae_device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int DMAOR_AE ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int dmaor_read (struct sh_dmae_device*) ; 
 int /*<<< orphan*/  sh_dmae_reset (struct sh_dmae_device*) ; 

__attribute__((used)) static irqreturn_t sh_dmae_err(int irq, void *data)
{
	struct sh_dmae_device *shdev = data;

	if (!(dmaor_read(shdev) & DMAOR_AE))
		return IRQ_NONE;

	sh_dmae_reset(shdev);
	return IRQ_HANDLED;
}