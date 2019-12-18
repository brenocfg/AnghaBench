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
typedef  scalar_t__ usb_error_t ;
typedef  int uint8_t ;
typedef  scalar_t__ uint16_t ;
struct usb_device_request {int bRequest; int /*<<< orphan*/  wIndex; int /*<<< orphan*/  wValue; int /*<<< orphan*/  bmRequestType; int /*<<< orphan*/  wLength; } ;
struct usb_device {int dummy; } ;
struct uaudio_mixer_node {int* wValue; scalar_t__ wIndex; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINTFN (int,char*,int) ; 
#define  GET_CUR 131 
#define  GET_MAX 130 
#define  GET_MIN 129 
#define  GET_RES 128 
 scalar_t__ MIX_SIZE (int /*<<< orphan*/ ) ; 
 int UA20_CS_CUR ; 
 int UA20_CS_RANGE ; 
 scalar_t__ UAUDIO_VERSION_20 ; 
 scalar_t__ UAUDIO_VERSION_30 ; 
 int /*<<< orphan*/  USETW (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  UT_READ_CLASS_INTERFACE ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int uaudio_mixer_signext (int /*<<< orphan*/ ,int) ; 
 scalar_t__ usbd_do_request (struct usb_device*,int /*<<< orphan*/ *,struct usb_device_request*,int*) ; 
 int /*<<< orphan*/  usbd_errstr (scalar_t__) ; 

__attribute__((used)) static int
uaudio_mixer_get(struct usb_device *udev, uint16_t audio_rev,
    uint8_t what, struct uaudio_mixer_node *mc)
{
	struct usb_device_request req;
	int val;
	uint8_t data[2 + (2 * 3)];
	usb_error_t err;

	if (mc->wValue[0] == -1)
		return (0);

	if (audio_rev >= UAUDIO_VERSION_30)
		return (0);
	else if (audio_rev >= UAUDIO_VERSION_20) {
		if (what == GET_CUR) {
			req.bRequest = UA20_CS_CUR;
			USETW(req.wLength, 2);
		} else {
			req.bRequest = UA20_CS_RANGE;
			USETW(req.wLength, 8);
		}
	} else {
		uint16_t len = MIX_SIZE(mc->type);

		req.bRequest = what;
		USETW(req.wLength, len);
	}

	req.bmRequestType = UT_READ_CLASS_INTERFACE;
	USETW(req.wValue, mc->wValue[0]);
	USETW(req.wIndex, mc->wIndex);

	memset(data, 0, sizeof(data));

	err = usbd_do_request(udev, NULL, &req, data);
	if (err) {
		DPRINTF("err=%s\n", usbd_errstr(err));
		return (0);
	}

	if (audio_rev >= UAUDIO_VERSION_30) {
		val = 0;
	} else if (audio_rev >= UAUDIO_VERSION_20) {
		switch (what) {
		case GET_CUR:
			val = (data[0] | (data[1] << 8));
			break;
		case GET_MIN:
			val = (data[2] | (data[3] << 8));
			break;
		case GET_MAX:
			val = (data[4] | (data[5] << 8));
			break;
		case GET_RES:
			val = (data[6] | (data[7] << 8));
			break;
		default:
			val = 0;
			break;
		}
	} else {
		val = (data[0] | (data[1] << 8));
	}

	if (what == GET_CUR || what == GET_MIN || what == GET_MAX)
		val = uaudio_mixer_signext(mc->type, val);

	DPRINTFN(3, "val=%d\n", val);

	return (val);
}