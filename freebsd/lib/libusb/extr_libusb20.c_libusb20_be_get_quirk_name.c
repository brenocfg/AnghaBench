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
typedef  int /*<<< orphan*/  uint16_t ;
struct libusb20_quirk {int dummy; } ;
struct libusb20_backend {TYPE_1__* methods; } ;
struct TYPE_2__ {int (* root_get_quirk_name ) (struct libusb20_backend*,int /*<<< orphan*/ ,struct libusb20_quirk*) ;} ;

/* Variables and functions */
 int stub1 (struct libusb20_backend*,int /*<<< orphan*/ ,struct libusb20_quirk*) ; 

int
libusb20_be_get_quirk_name(struct libusb20_backend *pbe,
    uint16_t quirk_index, struct libusb20_quirk *pq)
{
	return (pbe->methods->root_get_quirk_name(pbe, quirk_index, pq));
}