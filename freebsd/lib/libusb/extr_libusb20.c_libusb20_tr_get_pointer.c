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
typedef  scalar_t__ uint16_t ;
struct libusb20_transfer {int dummy; } ;
struct libusb20_device {scalar_t__ nTransfer; struct libusb20_transfer* pTransfer; } ;

/* Variables and functions */

struct libusb20_transfer *
libusb20_tr_get_pointer(struct libusb20_device *pdev, uint16_t trIndex)
{
	if (trIndex >= pdev->nTransfer) {
		return (NULL);
	}
	return (pdev->pTransfer + trIndex);
}