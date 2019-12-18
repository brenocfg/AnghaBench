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
struct device_link {void* status; } ;
struct TYPE_2__ {int status; } ;
struct device {TYPE_1__ links; } ;

/* Variables and functions */
#define  DL_DEV_DRIVER_BOUND 130 
#define  DL_DEV_PROBING 129 
#define  DL_DEV_UNBINDING 128 
 void* DL_STATE_ACTIVE ; 
 void* DL_STATE_AVAILABLE ; 
 void* DL_STATE_CONSUMER_PROBE ; 
 void* DL_STATE_DORMANT ; 
 void* DL_STATE_SUPPLIER_UNBIND ; 

__attribute__((used)) static void device_link_init_status(struct device_link *link,
				    struct device *consumer,
				    struct device *supplier)
{
	switch (supplier->links.status) {
	case DL_DEV_PROBING:
		switch (consumer->links.status) {
		case DL_DEV_PROBING:
			/*
			 * A consumer driver can create a link to a supplier
			 * that has not completed its probing yet as long as it
			 * knows that the supplier is already functional (for
			 * example, it has just acquired some resources from the
			 * supplier).
			 */
			link->status = DL_STATE_CONSUMER_PROBE;
			break;
		default:
			link->status = DL_STATE_DORMANT;
			break;
		}
		break;
	case DL_DEV_DRIVER_BOUND:
		switch (consumer->links.status) {
		case DL_DEV_PROBING:
			link->status = DL_STATE_CONSUMER_PROBE;
			break;
		case DL_DEV_DRIVER_BOUND:
			link->status = DL_STATE_ACTIVE;
			break;
		default:
			link->status = DL_STATE_AVAILABLE;
			break;
		}
		break;
	case DL_DEV_UNBINDING:
		link->status = DL_STATE_SUPPLIER_UNBIND;
		break;
	default:
		link->status = DL_STATE_DORMANT;
		break;
	}
}