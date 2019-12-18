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
struct hdmi_avi_infoframe {int version; int /*<<< orphan*/  length; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_AVI_INFOFRAME_SIZE ; 
 int /*<<< orphan*/  HDMI_INFOFRAME_TYPE_AVI ; 
 int /*<<< orphan*/  memset (struct hdmi_avi_infoframe*,int /*<<< orphan*/ ,int) ; 

int hdmi_avi_infoframe_init(struct hdmi_avi_infoframe *frame)
{
	memset(frame, 0, sizeof(*frame));

	frame->type = HDMI_INFOFRAME_TYPE_AVI;
	frame->version = 2;
	frame->length = HDMI_AVI_INFOFRAME_SIZE;

	return 0;
}