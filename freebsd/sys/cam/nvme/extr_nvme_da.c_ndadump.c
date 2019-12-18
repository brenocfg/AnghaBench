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
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  union ccb {int dummy; } ccb ;
typedef  size_t uint64_t ;
typedef  size_t uint32_t ;
typedef  size_t u_int ;
struct nda_softc {TYPE_1__* disk; } ;
struct disk {struct cam_periph* d_drv1; } ;
struct ccb_nvmeio {void* ccb_state; int /*<<< orphan*/  ccb_h; } ;
struct cam_periph {int flags; int /*<<< orphan*/  path; scalar_t__ softc; } ;
typedef  size_t off_t ;
typedef  int /*<<< orphan*/  nvmeio ;
struct TYPE_2__ {size_t d_sectorsize; } ;

/* Variables and functions */
 int CAM_PERIPH_INVALID ; 
 int /*<<< orphan*/  CAM_PRIORITY_NORMAL ; 
 int ENXIO ; 
 void* NDA_CCB_DUMP ; 
 int SF_NO_RECOVERY ; 
 int SF_NO_RETRY ; 
 int /*<<< orphan*/  cam_periph_error ; 
 int cam_periph_runccb (union ccb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct ccb_nvmeio*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nda_nvme_flush (struct nda_softc*,struct ccb_nvmeio*) ; 
 int /*<<< orphan*/  nda_nvme_write (struct nda_softc*,struct ccb_nvmeio*,void*,size_t,size_t,size_t) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  xpt_print (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xpt_setup_ccb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ndadump(void *arg, void *virtual, vm_offset_t physical, off_t offset, size_t length)
{
	struct	    cam_periph *periph;
	struct	    nda_softc *softc;
	u_int	    secsize;
	struct ccb_nvmeio nvmeio;
	struct	    disk *dp;
	uint64_t    lba;
	uint32_t    count;
	int	    error = 0;

	dp = arg;
	periph = dp->d_drv1;
	softc = (struct nda_softc *)periph->softc;
	secsize = softc->disk->d_sectorsize;
	lba = offset / secsize;
	count = length / secsize;
	
	if ((periph->flags & CAM_PERIPH_INVALID) != 0)
		return (ENXIO);

	/* xpt_get_ccb returns a zero'd allocation for the ccb, mimic that here */
	memset(&nvmeio, 0, sizeof(nvmeio));
	if (length > 0) {
		xpt_setup_ccb(&nvmeio.ccb_h, periph->path, CAM_PRIORITY_NORMAL);
		nvmeio.ccb_state = NDA_CCB_DUMP;
		nda_nvme_write(softc, &nvmeio, virtual, lba, length, count);
		error = cam_periph_runccb((union ccb *)&nvmeio, cam_periph_error,
		    0, SF_NO_RECOVERY | SF_NO_RETRY, NULL);
		if (error != 0)
			printf("Aborting dump due to I/O error %d.\n", error);

		return (error);
	}
	
	/* Flush */
	xpt_setup_ccb(&nvmeio.ccb_h, periph->path, CAM_PRIORITY_NORMAL);

	nvmeio.ccb_state = NDA_CCB_DUMP;
	nda_nvme_flush(softc, &nvmeio);
	error = cam_periph_runccb((union ccb *)&nvmeio, cam_periph_error,
	    0, SF_NO_RECOVERY | SF_NO_RETRY, NULL);
	if (error != 0)
		xpt_print(periph->path, "flush cmd failed\n");
	return (error);
}