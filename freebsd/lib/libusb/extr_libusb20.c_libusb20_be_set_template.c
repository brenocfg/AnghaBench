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
struct libusb20_backend {TYPE_1__* methods; } ;
struct TYPE_2__ {int (* root_set_template ) (struct libusb20_backend*,int) ;} ;

/* Variables and functions */
 int stub1 (struct libusb20_backend*,int) ; 

int
libusb20_be_set_template(struct libusb20_backend *pbe, int temp)
{
	return (pbe->methods->root_set_template(pbe, temp));
}