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
struct TYPE_2__ {int ExtPageLength; void* ExtPageType; void* PageNumber; void* PageVersion; } ;
struct mpt_ext_cfg_page_req {int len; int /*<<< orphan*/  ioc_status; TYPE_1__ header; void* buf; int /*<<< orphan*/  page_address; } ;
typedef  int /*<<< orphan*/  req ;
typedef  void* U8 ;
typedef  int /*<<< orphan*/  U32 ;
typedef  int /*<<< orphan*/  U16 ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  IOC_STATUS_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MPI_IOCSTATUS_SUCCESS ; 
 int /*<<< orphan*/  MPTIO_READ_EXT_CFG_HEADER ; 
 int /*<<< orphan*/  MPTIO_READ_EXT_CFG_PAGE ; 
 int /*<<< orphan*/  bcopy (TYPE_1__*,void*,int) ; 
 int /*<<< orphan*/  bzero (struct mpt_ext_cfg_page_req*,int) ; 
 int errno ; 
 int /*<<< orphan*/  free (void*) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct mpt_ext_cfg_page_req*) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  mpt_ioc_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ) ; 

void *
mpt_read_extended_config_page(int fd, U8 ExtPageType, U8 PageVersion,
    U8 PageNumber, U32 PageAddress, U16 *IOCStatus)
{
	struct mpt_ext_cfg_page_req req;
	void *buf;
	int error;

	if (IOCStatus != NULL)
		*IOCStatus = MPI_IOCSTATUS_SUCCESS;
	bzero(&req, sizeof(req));
	req.header.PageVersion = PageVersion;
	req.header.PageNumber = PageNumber;
	req.header.ExtPageType = ExtPageType;
	req.page_address = PageAddress;
	if (ioctl(fd, MPTIO_READ_EXT_CFG_HEADER, &req) < 0)
		return (NULL);
	if (!IOC_STATUS_SUCCESS(req.ioc_status)) {
		if (IOCStatus != NULL)
			*IOCStatus = req.ioc_status;
		else
			warnx("Reading extended config page header failed: %s",
			    mpt_ioc_status(req.ioc_status));
		errno = EIO;
		return (NULL);
	}
	req.len = req.header.ExtPageLength * 4;
	buf = malloc(req.len);
	req.buf = buf;
	bcopy(&req.header, buf, sizeof(req.header));
	if (ioctl(fd, MPTIO_READ_EXT_CFG_PAGE, &req) < 0) {
		error = errno;
		free(buf);
		errno = error;
		return (NULL);
	}
	if (!IOC_STATUS_SUCCESS(req.ioc_status)) {
		if (IOCStatus != NULL)
			*IOCStatus = req.ioc_status;
		else
			warnx("Reading extended config page failed: %s",
			    mpt_ioc_status(req.ioc_status));
		free(buf);
		errno = EIO;
		return (NULL);
	}
	return (buf);
}