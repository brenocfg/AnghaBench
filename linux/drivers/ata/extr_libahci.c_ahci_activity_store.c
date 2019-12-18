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
typedef  int u32 ;
struct ata_port {int port_no; TYPE_1__* ops; struct ahci_port_priv* private_data; } ;
struct ata_link {size_t pmp; int /*<<< orphan*/  flags; struct ata_port* ap; } ;
struct ata_device {struct ata_link* link; } ;
struct ahci_port_priv {struct ahci_em_priv* em_priv; } ;
struct ahci_em_priv {int led_state; int blink_policy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  enum sw_activity { ____Placeholder_sw_activity } sw_activity ;
struct TYPE_2__ {int /*<<< orphan*/  (* transmit_led_message ) (struct ata_port*,int,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_LFLAG_SW_ACTIVITY ; 
 int BLINK_OFF ; 
 int EM_MSG_LED_VALUE_OFF ; 
 int EM_MSG_LED_VALUE_ON ; 
 int OFF ; 
 int /*<<< orphan*/  stub1 (struct ata_port*,int,int) ; 
 int /*<<< orphan*/  stub2 (struct ata_port*,int,int) ; 

__attribute__((used)) static ssize_t ahci_activity_store(struct ata_device *dev, enum sw_activity val)
{
	struct ata_link *link = dev->link;
	struct ata_port *ap = link->ap;
	struct ahci_port_priv *pp = ap->private_data;
	struct ahci_em_priv *emp = &pp->em_priv[link->pmp];
	u32 port_led_state = emp->led_state;

	/* save the desired Activity LED behavior */
	if (val == OFF) {
		/* clear LFLAG */
		link->flags &= ~(ATA_LFLAG_SW_ACTIVITY);

		/* set the LED to OFF */
		port_led_state &= EM_MSG_LED_VALUE_OFF;
		port_led_state |= (ap->port_no | (link->pmp << 8));
		ap->ops->transmit_led_message(ap, port_led_state, 4);
	} else {
		link->flags |= ATA_LFLAG_SW_ACTIVITY;
		if (val == BLINK_OFF) {
			/* set LED to ON for idle */
			port_led_state &= EM_MSG_LED_VALUE_OFF;
			port_led_state |= (ap->port_no | (link->pmp << 8));
			port_led_state |= EM_MSG_LED_VALUE_ON; /* check this */
			ap->ops->transmit_led_message(ap, port_led_state, 4);
		}
	}
	emp->blink_policy = val;
	return 0;
}