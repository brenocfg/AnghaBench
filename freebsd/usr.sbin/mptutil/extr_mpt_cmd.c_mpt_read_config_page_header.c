#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void* PageNumber; void* PageType; } ;
struct mpt_cfg_page_req {TYPE_1__ header; int /*<<< orphan*/  ioc_status; int /*<<< orphan*/  page_address; } ;
typedef  int /*<<< orphan*/  req ;
typedef  void* U8 ;
typedef  int /*<<< orphan*/  U32 ;
typedef  int /*<<< orphan*/  U16 ;
typedef  TYPE_1__ CONFIG_PAGE_HEADER ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  IOC_STATUS_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MPI_IOCSTATUS_SUCCESS ; 
 int /*<<< orphan*/  MPTIO_READ_CFG_HEADER ; 
 int /*<<< orphan*/  bzero (struct mpt_cfg_page_req*,int) ; 
 int errno ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct mpt_cfg_page_req*) ; 
 int /*<<< orphan*/  mpt_ioc_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ) ; 

int
mpt_read_config_page_header(int fd, U8 PageType, U8 PageNumber, U32 PageAddress,
    CONFIG_PAGE_HEADER *header, U16 *IOCStatus)
{
	struct mpt_cfg_page_req req;

	if (IOCStatus != NULL)
		*IOCStatus = MPI_IOCSTATUS_SUCCESS;
	bzero(&req, sizeof(req));
	req.header.PageType = PageType;
	req.header.PageNumber = PageNumber;
	req.page_address = PageAddress;
	if (ioctl(fd, MPTIO_READ_CFG_HEADER, &req) < 0)
		return (errno);
	if (!IOC_STATUS_SUCCESS(req.ioc_status)) {
		if (IOCStatus != NULL)
			*IOCStatus = req.ioc_status;
		else
			warnx("Reading config page header failed: %s",
			    mpt_ioc_status(req.ioc_status));
		return (EIO);
	}
	*header = req.header;
	return (0);
}