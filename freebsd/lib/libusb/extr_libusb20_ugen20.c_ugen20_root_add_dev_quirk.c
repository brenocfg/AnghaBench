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
struct usb_gen_quirk {int /*<<< orphan*/  quirkname; int /*<<< orphan*/  bcdDeviceHigh; int /*<<< orphan*/  bcdDeviceLow; int /*<<< orphan*/  pid; int /*<<< orphan*/  vid; } ;
struct libusb20_quirk {int /*<<< orphan*/  quirkname; int /*<<< orphan*/  bcdDeviceHigh; int /*<<< orphan*/  bcdDeviceLow; int /*<<< orphan*/  pid; int /*<<< orphan*/  vid; } ;
struct libusb20_backend {int dummy; } ;
typedef  int /*<<< orphan*/  q ;

/* Variables and functions */
 scalar_t__ ENOMEM ; 
 int /*<<< orphan*/  IOUSB (int /*<<< orphan*/ ) ; 
 int LIBUSB20_ERROR_NO_MEM ; 
 int /*<<< orphan*/  USB_DEV_QUIRK_ADD ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  memset (struct usb_gen_quirk*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ugen20_be_ioctl (int /*<<< orphan*/ ,struct usb_gen_quirk*) ; 

__attribute__((used)) static int
ugen20_root_add_dev_quirk(struct libusb20_backend *pbe,
    struct libusb20_quirk *pq)
{
	struct usb_gen_quirk q;
	int error;

	memset(&q, 0, sizeof(q));

	q.vid = pq->vid;
	q.pid = pq->pid;
	q.bcdDeviceLow = pq->bcdDeviceLow;
	q.bcdDeviceHigh = pq->bcdDeviceHigh;
	strlcpy(q.quirkname, pq->quirkname, sizeof(q.quirkname));

	error = ugen20_be_ioctl(IOUSB(USB_DEV_QUIRK_ADD), &q);
	if (error) {
		if (errno == ENOMEM) {
			return (LIBUSB20_ERROR_NO_MEM);
		}
	}
	return (error);
}