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
typedef  int /*<<< orphan*/  ur ;
typedef  int u_long ;
struct usb_fifo {int dummy; } ;
struct TYPE_2__ {int bmRequestType; int /*<<< orphan*/  wLength; int /*<<< orphan*/  wIndex; int /*<<< orphan*/  wValue; int /*<<< orphan*/  bRequest; } ;
struct usb_ctl_request {int /*<<< orphan*/  ucr_data; TYPE_1__ ucr_request; } ;
struct RioCommand {int requesttype; int /*<<< orphan*/  buffer; int /*<<< orphan*/  length; int /*<<< orphan*/  index; int /*<<< orphan*/  value; int /*<<< orphan*/  request; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*) ; 
 int EINVAL ; 
 int EPERM ; 
 int FWRITE ; 
#define  RIO_RECV_COMMAND 129 
#define  RIO_SEND_COMMAND 128 
 int /*<<< orphan*/  USETW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int UT_READ_VENDOR_DEVICE ; 
 int UT_WRITE_VENDOR_DEVICE ; 
 int /*<<< orphan*/  memset (struct usb_ctl_request*,int /*<<< orphan*/ ,int) ; 
 int ugen_do_request (struct usb_fifo*,struct usb_ctl_request*) ; 

__attribute__((used)) static int
urio_ioctl(struct usb_fifo *fifo, u_long cmd, void *addr,
    int fflags)
{
	struct usb_ctl_request ur;
	struct RioCommand *rio_cmd;
	int error;

	switch (cmd) {
	case RIO_RECV_COMMAND:
		if (!(fflags & FWRITE)) {
			error = EPERM;
			goto done;
		}
		memset(&ur, 0, sizeof(ur));
		rio_cmd = addr;
		ur.ucr_request.bmRequestType =
		    rio_cmd->requesttype | UT_READ_VENDOR_DEVICE;
		break;

	case RIO_SEND_COMMAND:
		if (!(fflags & FWRITE)) {
			error = EPERM;
			goto done;
		}
		memset(&ur, 0, sizeof(ur));
		rio_cmd = addr;
		ur.ucr_request.bmRequestType =
		    rio_cmd->requesttype | UT_WRITE_VENDOR_DEVICE;
		break;

	default:
		error = EINVAL;
		goto done;
	}

	DPRINTFN(2, "Sending command\n");

	/* Send rio control message */
	ur.ucr_request.bRequest = rio_cmd->request;
	USETW(ur.ucr_request.wValue, rio_cmd->value);
	USETW(ur.ucr_request.wIndex, rio_cmd->index);
	USETW(ur.ucr_request.wLength, rio_cmd->length);
	ur.ucr_data = rio_cmd->buffer;

	/* reuse generic USB code */
	error = ugen_do_request(fifo, &ur);

done:
	return (error);
}