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
typedef  int /*<<< orphan*/  uint8_t ;
struct hdmi_spd_infoframe {int /*<<< orphan*/  sdi; int /*<<< orphan*/  product; int /*<<< orphan*/  vendor; } ;
struct hdmi_any_infoframe {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  hdmi_infoframe_log_header (struct hdmi_any_infoframe*) ; 
 int /*<<< orphan*/  hdmi_log (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  hdmi_spd_sdi_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hdmi_spd_infoframe_log(struct hdmi_spd_infoframe *frame)
{
	uint8_t buf[17];

	hdmi_infoframe_log_header((struct hdmi_any_infoframe *)frame);

	memset(buf, 0, sizeof(buf));

	strncpy(buf, frame->vendor, 8);
	hdmi_log("    vendor: %s\n", buf);
	strncpy(buf, frame->product, 16);
	hdmi_log("    product: %s\n", buf);
	hdmi_log("    source device information: %s (0x%x)\n",
		hdmi_spd_sdi_get_name(frame->sdi), frame->sdi);
}