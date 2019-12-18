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
struct iwmbt_firmware {int dummy; } ;
typedef  int /*<<< orphan*/  libusb_device_handle ;

/* Variables and functions */
 int /*<<< orphan*/  iwmbt_debug (char*,...) ; 
 int /*<<< orphan*/  iwmbt_fw_free (struct iwmbt_firmware*) ; 
 scalar_t__ iwmbt_fw_read (struct iwmbt_firmware*,char const*) ; 
 int iwmbt_load_ddc (int /*<<< orphan*/ *,struct iwmbt_firmware*) ; 

__attribute__((used)) static int
iwmbt_init_ddc(libusb_device_handle *hdl, const char *ddc_path)
{
	struct iwmbt_firmware ddc;
	int ret;

	iwmbt_debug("loading %s", ddc_path);

	/* Read in the DDC file */
	if (iwmbt_fw_read(&ddc, ddc_path) <= 0) {
		iwmbt_debug("iwmbt_fw_read() failed");
		return (-1);
	}

	/* Load in the DDC file */
	ret = iwmbt_load_ddc(hdl, &ddc);
	if (ret < 0)
		iwmbt_debug("Loading DDC file failed");

	/* free it */
	iwmbt_fw_free(&ddc);

	return (ret);
}