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
struct usb_dmac_chan {int /*<<< orphan*/  irq; } ;
struct usb_dmac {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  devm_free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct usb_dmac_chan*) ; 
 int /*<<< orphan*/  usb_dmac_chan_halt (struct usb_dmac_chan*) ; 

__attribute__((used)) static void usb_dmac_chan_remove(struct usb_dmac *dmac,
				 struct usb_dmac_chan *uchan)
{
	usb_dmac_chan_halt(uchan);
	devm_free_irq(dmac->dev, uchan->irq, uchan);
}