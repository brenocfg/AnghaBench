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
typedef  int /*<<< orphan*/  uint32_t ;
struct iwmbt_firmware {int dummy; } ;
typedef  int /*<<< orphan*/  libusb_device_handle ;

/* Variables and functions */
 int /*<<< orphan*/  iwmbt_debug (char*,...) ; 
 int /*<<< orphan*/  iwmbt_fw_free (struct iwmbt_firmware*) ; 
 scalar_t__ iwmbt_fw_read (struct iwmbt_firmware*,char const*) ; 
 int iwmbt_load_fwfile (int /*<<< orphan*/ *,struct iwmbt_firmware*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
iwmbt_init_firmware(libusb_device_handle *hdl, const char *firmware_path,
    uint32_t *boot_param)
{
	struct iwmbt_firmware fw;
	int ret;

	iwmbt_debug("loading %s", firmware_path);

	/* Read in the firmware */
	if (iwmbt_fw_read(&fw, firmware_path) <= 0) {
		iwmbt_debug("iwmbt_fw_read() failed");
		return (-1);
	}

	/* Load in the firmware */
	ret = iwmbt_load_fwfile(hdl, &fw, boot_param);
	if (ret < 0)
		iwmbt_debug("Loading firmware file failed");

	/* free it */
	iwmbt_fw_free(&fw);

	return (ret);
}