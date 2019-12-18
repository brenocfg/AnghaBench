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
struct usb_endpoint {int isoc_next; int toggle_next; TYPE_1__* edesc; } ;
struct TYPE_2__ {int bEndpointAddress; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  usb_dump_queue (struct usb_endpoint*) ; 

void
usb_dump_endpoint(struct usb_endpoint *ep)
{
	if (ep) {
		printf("usb_dump_endpoint: endpoint=%p", ep);

		printf(" edesc=%p isoc_next=%d toggle_next=%d",
		    ep->edesc, ep->isoc_next, ep->toggle_next);

		if (ep->edesc) {
			printf(" bEndpointAddress=0x%02x",
			    ep->edesc->bEndpointAddress);
		}
		printf("\n");
		usb_dump_queue(ep);
	} else {
		printf("usb_dump_endpoint: endpoint=NULL\n");
	}
}