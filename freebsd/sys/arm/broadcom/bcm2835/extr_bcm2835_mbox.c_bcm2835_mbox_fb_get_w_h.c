#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_9__ {TYPE_3__ resp; } ;
struct TYPE_7__ {scalar_t__ val_len; } ;
struct TYPE_10__ {TYPE_4__ body; TYPE_2__ tag_hdr; } ;
struct TYPE_6__ {int buf_size; int /*<<< orphan*/  code; } ;
struct msg_fb_get_w_h {TYPE_5__ physical_w_h; scalar_t__ end_tag; TYPE_1__ hdr; } ;
struct bcm2835_fb_config {int /*<<< orphan*/  yres; int /*<<< orphan*/  xres; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  BCM2835_MBOX_CODE_REQ ; 
 int /*<<< orphan*/  BCM2835_MBOX_INIT_TAG (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_PHYSICAL_W_H ; 
 int bcm2835_mbox_property (struct msg_fb_get_w_h*,int) ; 
 int /*<<< orphan*/  memset (struct msg_fb_get_w_h*,int /*<<< orphan*/ ,int) ; 

int
bcm2835_mbox_fb_get_w_h(struct bcm2835_fb_config *fb)
{
	int err;
	struct msg_fb_get_w_h msg;

	memset(&msg, 0, sizeof(msg));
	msg.hdr.buf_size = sizeof(msg);
	msg.hdr.code = BCM2835_MBOX_CODE_REQ;
	BCM2835_MBOX_INIT_TAG(&msg.physical_w_h, GET_PHYSICAL_W_H);
	msg.physical_w_h.tag_hdr.val_len = 0;
	msg.end_tag = 0;

	err = bcm2835_mbox_property(&msg, sizeof(msg));
	if (err == 0) {
		fb->xres = msg.physical_w_h.body.resp.width;
		fb->yres = msg.physical_w_h.body.resp.height;
	}

	return (err);
}