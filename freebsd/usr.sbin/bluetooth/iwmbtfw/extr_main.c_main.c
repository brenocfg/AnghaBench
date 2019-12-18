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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct iwmbt_version {int fw_variant; } ;
struct iwmbt_boot_params {int limited_cce; } ;
typedef  int /*<<< orphan*/  libusb_device_handle ;
typedef  int /*<<< orphan*/  libusb_device ;
typedef  int /*<<< orphan*/  libusb_context ;

/* Variables and functions */
 int /*<<< orphan*/  _DEFAULT_IWMBT_FIRMWARE_PATH ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  iwmbt_debug (char*,...) ; 
 int iwmbt_do_debug ; 
 int iwmbt_do_info ; 
 int /*<<< orphan*/  iwmbt_dump_boot_params (struct iwmbt_boot_params*) ; 
 int /*<<< orphan*/  iwmbt_dump_version (struct iwmbt_version*) ; 
 int /*<<< orphan*/  iwmbt_err (char*,...) ; 
 int /*<<< orphan*/ * iwmbt_find_device (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int iwmbt_get_boot_params (int /*<<< orphan*/ *,struct iwmbt_boot_params*) ; 
 char* iwmbt_get_fwname (struct iwmbt_version*,struct iwmbt_boot_params*,char*,char*) ; 
 int iwmbt_get_version (int /*<<< orphan*/ *,struct iwmbt_version*) ; 
 int /*<<< orphan*/  iwmbt_info (char*) ; 
 int iwmbt_init_ddc (int /*<<< orphan*/ *,char*) ; 
 int iwmbt_init_firmware (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int iwmbt_intel_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int iwmbt_set_event_mask (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libusb_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libusb_exit (int /*<<< orphan*/ *) ; 
 int libusb_init (int /*<<< orphan*/ **) ; 
 int libusb_kernel_driver_active (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int libusb_open (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int libusb_reset_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libusb_strerror (int) ; 
 int /*<<< orphan*/  libusb_unref_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  optarg ; 
 int /*<<< orphan*/  parse_ugen_name (int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 
 char* strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{
	libusb_context *ctx = NULL;
	libusb_device *dev = NULL;
	libusb_device_handle *hdl = NULL;
	static struct iwmbt_version ver;
	static struct iwmbt_boot_params params;
	uint32_t boot_param;
	int r;
	uint8_t bus_id = 0, dev_id = 0;
	int devid_set = 0;
	int n;
	char *firmware_dir = NULL;
	char *firmware_path = NULL;
	int retcode = 1;

	/* Parse command line arguments */
	while ((n = getopt(argc, argv, "Dd:f:hIm:p:v:")) != -1) {
		switch (n) {
		case 'd': /* ugen device name */
			devid_set = 1;
			if (parse_ugen_name(optarg, &bus_id, &dev_id) < 0)
				usage();
			break;
		case 'D':
			iwmbt_do_debug = 1;
			break;
		case 'f': /* firmware dir */
			if (firmware_dir)
				free(firmware_dir);
			firmware_dir = strdup(optarg);
			break;
		case 'I':
			iwmbt_do_info = 1;
			break;
		case 'h':
		default:
			usage();
			break;
			/* NOT REACHED */
		}
	}

	/* Ensure the devid was given! */
	if (devid_set == 0) {
		usage();
		/* NOTREACHED */
	}

	/* libusb setup */
	r = libusb_init(&ctx);
	if (r != 0) {
		iwmbt_err("libusb_init failed: code %d", r);
		exit(127);
	}

	iwmbt_debug("opening dev %d.%d", (int) bus_id, (int) dev_id);

	/* Find a device based on the bus/dev id */
	dev = iwmbt_find_device(ctx, bus_id, dev_id);
	if (dev == NULL) {
		iwmbt_err("device not found");
		goto shutdown;
	}

	/* XXX enforce that bInterfaceNumber is 0 */

	/* XXX enforce the device/product id if they're non-zero */

	/* Grab device handle */
	r = libusb_open(dev, &hdl);
	if (r != 0) {
		iwmbt_err("libusb_open() failed: code %d", r);
		goto shutdown;
	}

	/* Check if ng_ubt is attached */
	r = libusb_kernel_driver_active(hdl, 0);
	if (r < 0) {
		iwmbt_err("libusb_kernel_driver_active() failed: code %d", r);
		goto shutdown;
	}
	if (r > 0) {
		iwmbt_info("Firmware has already been downloaded");
		retcode = 0;
		goto shutdown;
	}

	/* Get Intel version */
	r = iwmbt_get_version(hdl, &ver);
	if (r < 0) {
		iwmbt_debug("iwmbt_get_version() failedL code %d", r);
		goto shutdown;
	}
	iwmbt_dump_version(&ver);
	iwmbt_debug("fw_variant=0x%02x", (int) ver.fw_variant);

	/* fw_variant = 0x06 bootloader mode / 0x23 operational mode */
	if (ver.fw_variant == 0x23) {
		iwmbt_info("Firmware has already been downloaded");
		retcode = 0;
		goto reset;
	}

	if (ver.fw_variant != 0x06){
		iwmbt_err("unknown fw_variant 0x%02x", (int) ver.fw_variant);
		goto shutdown;
	}

	/* Read Intel Secure Boot Params */
	r = iwmbt_get_boot_params(hdl, &params);
	if (r < 0) {
		iwmbt_debug("iwmbt_get_boot_params() failed!");
		goto shutdown;
	}
	iwmbt_dump_boot_params(&params);

	/* Check if firmware fragments are ACKed with a cmd complete event */
	if (params.limited_cce != 0x00) {
		iwmbt_err("Unsupported Intel firmware loading method (%u)",
		   params.limited_cce);
		goto shutdown;
	}

	/* Default the firmware path */
	if (firmware_dir == NULL)
		firmware_dir = strdup(_DEFAULT_IWMBT_FIRMWARE_PATH);

	firmware_path = iwmbt_get_fwname(&ver, &params, firmware_dir, "sfi");
	if (firmware_path == NULL)
		goto shutdown;

	iwmbt_debug("firmware_path = %s", firmware_path);

	/* Download firmware and parse it for magic Intel Reset parameter */
	r = iwmbt_init_firmware(hdl, firmware_path, &boot_param);
	free(firmware_path);
	if (r < 0)
		goto shutdown;

	iwmbt_info("Firmware download complete");

	r = iwmbt_intel_reset(hdl, boot_param);
	if (r < 0) {
		iwmbt_debug("iwmbt_intel_reset() failed!");
		goto shutdown;
	}

	iwmbt_info("Firmware operational");

	/* Once device is running in operational mode we can ignore failures */
	retcode = 0;

	/* Execute Read Intel Version one more time */
	r = iwmbt_get_version(hdl, &ver);
	if (r == 0)
		iwmbt_dump_version(&ver);

	/* Apply the device configuration (DDC) parameters */
	firmware_path = iwmbt_get_fwname(&ver, &params, firmware_dir, "ddc");
	iwmbt_debug("ddc_path = %s", firmware_path);
	if (firmware_path != NULL) {
		r = iwmbt_init_ddc(hdl, firmware_path);
		if (r == 0)
			iwmbt_info("DDC download complete");
		free(firmware_path);
	}

	/* Set Intel Event mask */
	r = iwmbt_set_event_mask(hdl);
	if (r == 0)
		iwmbt_info("Intel Event Mask is set");

reset:

	/* Ask kernel driver to probe and attach device again */
	r = libusb_reset_device(hdl);
	if (r != 0)
		iwmbt_err("libusb_reset_device() failed: %s",
		    libusb_strerror(r));

shutdown:

	/* Shutdown */

	if (hdl != NULL)
		libusb_close(hdl);

	if (dev != NULL)
		libusb_unref_device(dev);

	if (ctx != NULL)
		libusb_exit(ctx);

	if (retcode == 0)
		iwmbt_info("Firmware download is succesful!");
	else
		iwmbt_err("Firmware download failed!");

	return (retcode);
}