#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int Function; } ;
struct TYPE_3__ {int SGLOffset0; } ;
typedef  TYPE_1__ MPI2_SCSI_IO_REQUEST ;
typedef  TYPE_2__ MPI2_REQUEST_HEADER ;

/* Variables and functions */
#define  MPI2_FUNCTION_SCSI_IO_REQUEST 128 

__attribute__((used)) static int
find_sgl(char *buf)
{
	MPI2_REQUEST_HEADER *req;
	MPI2_SCSI_IO_REQUEST *scsi;
	int offset = 0;

	req = (MPI2_REQUEST_HEADER *)buf;

	switch (req->Function) {
	case MPI2_FUNCTION_SCSI_IO_REQUEST:
		scsi = (MPI2_SCSI_IO_REQUEST *)buf;
		offset = scsi->SGLOffset0;
		break;
	default:
		offset = -1;
	}

	return (offset);
}