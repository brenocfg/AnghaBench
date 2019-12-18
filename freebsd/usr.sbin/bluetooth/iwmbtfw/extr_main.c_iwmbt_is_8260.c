#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct libusb_device_descriptor {scalar_t__ idProduct; scalar_t__ idVendor; } ;
struct TYPE_3__ {scalar_t__ product_id; scalar_t__ vendor_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  iwmbt_info (char*) ; 
 TYPE_1__* iwmbt_list ; 
 scalar_t__ nitems (TYPE_1__*) ; 

__attribute__((used)) static int
iwmbt_is_8260(struct libusb_device_descriptor *d)
{
	int i;

	/* Search looking for whether it's an 8260/8265 */
	for (i = 0; i < (int) nitems(iwmbt_list); i++) {
		if ((iwmbt_list[i].product_id == d->idProduct) &&
		    (iwmbt_list[i].vendor_id == d->idVendor)) {
			iwmbt_info("found 8260/8265");
			return (1);
		}
	}

	/* Not found */
	return (0);
}