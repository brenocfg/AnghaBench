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
struct mpt_cfg_page_req {int len; int /*<<< orphan*/  ioc_status; void* buf; } ;
typedef  int /*<<< orphan*/  req ;
typedef  int /*<<< orphan*/  U16 ;
struct TYPE_2__ {int PageLength; } ;
typedef  TYPE_1__ CONFIG_PAGE_HEADER ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  IOC_STATUS_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MPI_IOCSTATUS_SUCCESS ; 
 int /*<<< orphan*/  MPTIO_WRITE_CFG_PAGE ; 
 int /*<<< orphan*/  bzero (struct mpt_cfg_page_req*,int) ; 
 int errno ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct mpt_cfg_page_req*) ; 
 int /*<<< orphan*/  mpt_ioc_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ) ; 

int
mpt_write_config_page(int fd, void *buf, U16 *IOCStatus)
{
	CONFIG_PAGE_HEADER *hdr;
	struct mpt_cfg_page_req req;

	if (IOCStatus != NULL)
		*IOCStatus = MPI_IOCSTATUS_SUCCESS;
	bzero(&req, sizeof(req));
	req.buf = buf;
	hdr = buf;
	req.len = hdr->PageLength * 4;
	if (ioctl(fd, MPTIO_WRITE_CFG_PAGE, &req) < 0)
		return (errno);
	if (!IOC_STATUS_SUCCESS(req.ioc_status)) {
		if (IOCStatus != NULL) {
			*IOCStatus = req.ioc_status;
			return (0);
		}
		warnx("Writing config page failed: %s",
		    mpt_ioc_status(req.ioc_status));
		return (EIO);
	}
	return (0);
}