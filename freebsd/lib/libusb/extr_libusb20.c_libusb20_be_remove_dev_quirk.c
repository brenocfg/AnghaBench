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
struct libusb20_quirk {int dummy; } ;
struct libusb20_backend {TYPE_1__* methods; } ;
struct TYPE_2__ {int (* root_remove_dev_quirk ) (struct libusb20_backend*,struct libusb20_quirk*) ;} ;

/* Variables and functions */
 int stub1 (struct libusb20_backend*,struct libusb20_quirk*) ; 

int
libusb20_be_remove_dev_quirk(struct libusb20_backend *pbe,
    struct libusb20_quirk *pq)
{
	return (pbe->methods->root_remove_dev_quirk(pbe, pq));
}