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
typedef  int uint32_t ;
struct ccb_getdev {int /*<<< orphan*/  protocol; } ;
struct cam_status_entry {char* status_text; } ;
struct cam_periph {int dummy; } ;
struct cam_path {int dummy; } ;
typedef  int cam_status ;

/* Variables and functions */
#define  AC_FOUND_DEVICE 128 
 int /*<<< orphan*/  CAM_PERIPH_BIO ; 
 int CAM_REQ_CMP ; 
 int CAM_REQ_INPROG ; 
 int /*<<< orphan*/  PROTO_SCSI ; 
 struct cam_status_entry* cam_fetch_status_entry (int) ; 
 int cam_periph_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,struct cam_path*,void (*) (void*,int,struct cam_path*,void*),int const,struct ccb_getdev*) ; 
 int /*<<< orphan*/  cam_periph_async (struct cam_periph*,int,struct cam_path*,void*) ; 
 int /*<<< orphan*/  printf (char*,int,char*) ; 
 int /*<<< orphan*/  sgcleanup ; 
 int /*<<< orphan*/  sgoninvalidate ; 
 int /*<<< orphan*/  sgregister ; 

__attribute__((used)) static void
sgasync(void *callback_arg, uint32_t code, struct cam_path *path, void *arg)
{
	struct cam_periph *periph;

	periph = (struct cam_periph *)callback_arg;

	switch (code) {
	case AC_FOUND_DEVICE:
	{
		struct ccb_getdev *cgd;
		cam_status status;

		cgd = (struct ccb_getdev *)arg;
		if (cgd == NULL)
			break;

		if (cgd->protocol != PROTO_SCSI)
			break;

		/*
		 * Allocate a peripheral instance for this device and
		 * start the probe process.
		 */
		status = cam_periph_alloc(sgregister, sgoninvalidate,
					  sgcleanup, NULL, "sg",
					  CAM_PERIPH_BIO, path,
					  sgasync, AC_FOUND_DEVICE, cgd);
		if ((status != CAM_REQ_CMP) && (status != CAM_REQ_INPROG)) {
			const struct cam_status_entry *entry;

			entry = cam_fetch_status_entry(status);
			printf("sgasync: Unable to attach new device "
				"due to status %#x: %s\n", status, entry ?
				entry->status_text : "Unknown");
		}
		break;
	}
	default:
		cam_periph_async(periph, code, path, arg);
		break;
	}
}