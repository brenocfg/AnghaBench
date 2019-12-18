#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  req ;
typedef  int /*<<< orphan*/  reply ;
typedef  void* U8 ;
typedef  int /*<<< orphan*/  U32 ;
typedef  int /*<<< orphan*/  U16 ;
struct TYPE_9__ {int /*<<< orphan*/  Header; int /*<<< orphan*/  IOCStatus; } ;
struct TYPE_7__ {void* PageNumber; void* PageType; } ;
struct TYPE_8__ {int /*<<< orphan*/  PageAddress; TYPE_1__ Header; int /*<<< orphan*/  Action; int /*<<< orphan*/  Function; } ;
typedef  TYPE_2__ MPI2_CONFIG_REQUEST ;
typedef  TYPE_3__ MPI2_CONFIG_REPLY ;
typedef  int /*<<< orphan*/  MPI2_CONFIG_PAGE_HEADER ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  IOC_STATUS_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MPI2_CONFIG_ACTION_PAGE_HEADER ; 
 int /*<<< orphan*/  MPI2_FUNCTION_CONFIG ; 
 int /*<<< orphan*/  bzero (TYPE_2__*,int) ; 
 int errno ; 
 scalar_t__ mps_pass_command (int,TYPE_2__*,int,TYPE_3__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int
mps_read_config_page_header(int fd, U8 PageType, U8 PageNumber, U32 PageAddress,
    MPI2_CONFIG_PAGE_HEADER *header, U16 *IOCStatus)
{
	MPI2_CONFIG_REQUEST req;
	MPI2_CONFIG_REPLY reply;

	bzero(&req, sizeof(req));
	req.Function = MPI2_FUNCTION_CONFIG;
	req.Action = MPI2_CONFIG_ACTION_PAGE_HEADER;
	req.Header.PageType = PageType;
	req.Header.PageNumber = PageNumber;
	req.PageAddress = PageAddress;

	if (mps_pass_command(fd, &req, sizeof(req), &reply, sizeof(reply),
	    NULL, 0, NULL, 0, 30))
		return (errno);

	if (!IOC_STATUS_SUCCESS(reply.IOCStatus)) {
		if (IOCStatus != NULL)
			*IOCStatus = reply.IOCStatus;
		return (EIO);
	}
	if (header == NULL)
		return (EINVAL);
	*header = reply.Header;
	return (0);
}