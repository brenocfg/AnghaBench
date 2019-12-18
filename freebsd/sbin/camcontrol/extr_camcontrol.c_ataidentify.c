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
typedef  union ccb {int dummy; } ccb ;
typedef  int /*<<< orphan*/  u_int64_t ;
struct cam_device {char* device_name; int /*<<< orphan*/  dev_unit_num; } ;
struct TYPE_2__ {int command1; } ;
struct ata_params {int support2; TYPE_1__ support; } ;

/* Variables and functions */
 int ATA_SUPPORT_AMAX_ADDR ; 
 int ATA_SUPPORT_PROTECTED ; 
 int CAM_ARG_VERBOSE ; 
 int arglist ; 
 scalar_t__ ata_do_identify (struct cam_device*,int,int,union ccb*,struct ata_params**) ; 
 int /*<<< orphan*/  ata_get_native_max (struct cam_device*,int,int,union ccb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ata_print_ident (struct ata_params*) ; 
 int /*<<< orphan*/  ata_read_native_max (struct cam_device*,int,int,union ccb*,struct ata_params*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ataama_print (struct ata_params*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atacapprint (struct ata_params*) ; 
 int /*<<< orphan*/  atahpa_print (struct ata_params*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_freeccb (union ccb*) ; 
 union ccb* cam_getccb (struct cam_device*) ; 
 int /*<<< orphan*/  camxferrate (struct cam_device*) ; 
 int /*<<< orphan*/  dump_data (void*,int) ; 
 int /*<<< orphan*/  free (struct ata_params*) ; 
 int /*<<< orphan*/  printf (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static int
ataidentify(struct cam_device *device, int retry_count, int timeout)
{
	union ccb *ccb;
	struct ata_params *ident_buf;
	u_int64_t hpasize = 0, nativesize = 0;

	if ((ccb = cam_getccb(device)) == NULL) {
		warnx("couldn't allocate CCB");
		return (1);
	}

	if (ata_do_identify(device, retry_count, timeout, ccb, &ident_buf) != 0) {
		cam_freeccb(ccb);
		return (1);
	}

	if (arglist & CAM_ARG_VERBOSE) {
		printf("%s%d: Raw identify data:\n",
		    device->device_name, device->dev_unit_num);
		dump_data((void*)ident_buf, sizeof(struct ata_params));
	}

	if (ident_buf->support.command1 & ATA_SUPPORT_PROTECTED) {
		ata_read_native_max(device, retry_count, timeout, ccb,
				    ident_buf, &hpasize);
	}
	if (ident_buf->support2 & ATA_SUPPORT_AMAX_ADDR) {
		ata_get_native_max(device, retry_count, timeout, ccb,
				   &nativesize);
	}

	printf("%s%d: ", device->device_name, device->dev_unit_num);
	ata_print_ident(ident_buf);
	camxferrate(device);
	atacapprint(ident_buf);
	atahpa_print(ident_buf, hpasize, 0);
	ataama_print(ident_buf, nativesize, 0);

	free(ident_buf);
	cam_freeccb(ccb);

	return (0);
}