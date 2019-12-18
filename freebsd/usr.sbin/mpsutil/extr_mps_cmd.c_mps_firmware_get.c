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
typedef  int /*<<< orphan*/  req ;
typedef  int /*<<< orphan*/  reply ;
struct TYPE_6__ {int ActualImageSize; int /*<<< orphan*/  ImageType; int /*<<< orphan*/  Function; } ;
typedef  TYPE_1__ MPI2_FW_UPLOAD_REQUEST ;
typedef  TYPE_1__ MPI2_FW_UPLOAD_REPLY ;

/* Variables and functions */
 int /*<<< orphan*/  MPI2_FUNCTION_FW_UPLOAD ; 
 int /*<<< orphan*/  MPI2_FW_DOWNLOAD_ITYPE_BIOS ; 
 int /*<<< orphan*/  MPI2_FW_DOWNLOAD_ITYPE_FW ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 unsigned char* calloc (int,int) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 scalar_t__ mps_user_command (int,TYPE_1__*,int,TYPE_1__*,int,unsigned char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*) ; 

int
mps_firmware_get(int fd, unsigned char **firmware, bool bios)
{
	MPI2_FW_UPLOAD_REQUEST req;
	MPI2_FW_UPLOAD_REPLY reply;
	int size;

	*firmware = NULL;
	bzero(&req, sizeof(req));
	bzero(&reply, sizeof(reply));
	req.Function = MPI2_FUNCTION_FW_UPLOAD;
	req.ImageType = bios ? MPI2_FW_DOWNLOAD_ITYPE_BIOS : MPI2_FW_DOWNLOAD_ITYPE_FW;

	if (mps_user_command(fd, &req, sizeof(req), &reply, sizeof(reply),
	    NULL, 0, 0)) {
		return (-1);
	}
	if (reply.ActualImageSize == 0) {
		return (-1);
	}

	size = reply.ActualImageSize;
	*firmware = calloc(size, sizeof(unsigned char));
	if (*firmware == NULL) {
		warn("calloc");
		return (-1);
	}
	if (mps_user_command(fd, &req, sizeof(req), &reply, sizeof(reply),
	    *firmware, size, 0)) {
		free(*firmware);
		return (-1);
	}

	return (size);
}