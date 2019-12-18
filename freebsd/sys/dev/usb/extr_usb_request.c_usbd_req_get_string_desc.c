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
typedef  int /*<<< orphan*/  usb_error_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct usb_device {int dummy; } ;
struct mtx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UDESC_STRING ; 
 int /*<<< orphan*/  usbd_req_get_desc (struct usb_device*,struct mtx*,int /*<<< orphan*/ *,void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

usb_error_t
usbd_req_get_string_desc(struct usb_device *udev, struct mtx *mtx, void *sdesc,
    uint16_t max_len, uint16_t lang_id,
    uint8_t string_index)
{
	return (usbd_req_get_desc(udev, mtx, NULL, sdesc, 2, max_len, lang_id,
	    UDESC_STRING, string_index, 0));
}