#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  req ;
typedef  int /*<<< orphan*/  reply ;
struct TYPE_6__ {int /*<<< orphan*/  MsgFlags; int /*<<< orphan*/  TotalImageSize; int /*<<< orphan*/  ImageType; int /*<<< orphan*/  Function; } ;
typedef  TYPE_1__ MPI2_FW_DOWNLOAD_REQUEST ;
typedef  TYPE_1__ MPI2_FW_DOWNLOAD_REPLY ;

/* Variables and functions */
 int /*<<< orphan*/  MPI2_FUNCTION_FW_DOWNLOAD ; 
 int /*<<< orphan*/  MPI2_FW_DOWNLOAD_ITYPE_BIOS ; 
 int /*<<< orphan*/  MPI2_FW_DOWNLOAD_ITYPE_FW ; 
 int /*<<< orphan*/  MPI2_FW_DOWNLOAD_MSGFLGS_LAST_SEGMENT ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 scalar_t__ mps_user_command (int,TYPE_1__*,int,TYPE_1__*,int,unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
mps_firmware_send(int fd, unsigned char *fw, uint32_t len, bool bios)
{
	MPI2_FW_DOWNLOAD_REQUEST req;
	MPI2_FW_DOWNLOAD_REPLY reply;

	bzero(&req, sizeof(req));
	bzero(&reply, sizeof(reply));
	req.Function = MPI2_FUNCTION_FW_DOWNLOAD;
	req.ImageType = bios ? MPI2_FW_DOWNLOAD_ITYPE_BIOS : MPI2_FW_DOWNLOAD_ITYPE_FW;
	req.TotalImageSize = len;
	req.MsgFlags = MPI2_FW_DOWNLOAD_MSGFLGS_LAST_SEGMENT;

	if (mps_user_command(fd, &req, sizeof(req), &reply, sizeof(reply),
	    fw, len, 0)) {
		return (-1);
	}
	return (0);
}