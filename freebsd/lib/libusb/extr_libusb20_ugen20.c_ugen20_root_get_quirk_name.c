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
typedef  int /*<<< orphan*/  uint16_t ;
struct usb_gen_quirk {int /*<<< orphan*/  quirkname; int /*<<< orphan*/  index; } ;
struct libusb20_quirk {int /*<<< orphan*/  quirkname; } ;
struct libusb20_backend {int dummy; } ;
typedef  int /*<<< orphan*/  q ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 int /*<<< orphan*/  IOUSB (int /*<<< orphan*/ ) ; 
 int LIBUSB20_ERROR_NOT_FOUND ; 
 int /*<<< orphan*/  USB_QUIRK_NAME_GET ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  memset (struct usb_gen_quirk*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ugen20_be_ioctl (int /*<<< orphan*/ ,struct usb_gen_quirk*) ; 

__attribute__((used)) static int
ugen20_root_get_quirk_name(struct libusb20_backend *pbe, uint16_t quirk_index,
    struct libusb20_quirk *pq)
{
	struct usb_gen_quirk q;
	int error;

	memset(&q, 0, sizeof(q));

	q.index = quirk_index;

	error = ugen20_be_ioctl(IOUSB(USB_QUIRK_NAME_GET), &q);

	if (error) {
		if (errno == EINVAL) {
			return (LIBUSB20_ERROR_NOT_FOUND);
		}
	} else {
		strlcpy(pq->quirkname, q.quirkname, sizeof(pq->quirkname));
	}
	return (error);
}