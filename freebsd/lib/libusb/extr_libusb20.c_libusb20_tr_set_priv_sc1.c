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
struct libusb20_transfer {void* priv_sc1; } ;

/* Variables and functions */

void
libusb20_tr_set_priv_sc1(struct libusb20_transfer *xfer, void *sc1)
{
	xfer->priv_sc1 = sc1;
	return;
}