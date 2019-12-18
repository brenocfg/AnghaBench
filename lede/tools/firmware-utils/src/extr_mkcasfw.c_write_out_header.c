#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {void* fs_csum; void* fs_size; void* fs_offs; void* kernel_csum; void* kernel_size; void* kernel_offs; void* id; void* type; } ;
struct TYPE_10__ {void* magic3; void* magic2; void* magic1; void* kernel_csum; void* kernel_size; void* kernel_offs; void* id; void* type; } ;
union file_hdr {TYPE_4__ nfs; TYPE_2__ cas; } ;
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_16__ {int header_type; } ;
struct TYPE_15__ {int out_size; int csum; } ;
struct TYPE_11__ {int type; int id; } ;
struct TYPE_9__ {int type; int id; } ;
struct TYPE_14__ {TYPE_3__ nfs; TYPE_1__ cas; } ;
struct TYPE_13__ {int out_size; int csum; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int CAS_MAGIC1 ; 
 int CAS_MAGIC2 ; 
 int CAS_MAGIC3 ; 
 int /*<<< orphan*/  ERRS (char*) ; 
 int ERR_FATAL ; 
#define  HEADER_TYPE_CAS 129 
#define  HEADER_TYPE_NFS 128 
 void* HOST_TO_LE32 (int) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 TYPE_8__* board ; 
 scalar_t__ errno ; 
 TYPE_7__ fs_image ; 
 scalar_t__ fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_6__ header ; 
 TYPE_5__ kernel_image ; 
 int write_out_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

int
write_out_header(FILE *outfile)
{
	union file_hdr tmp;
	int res;

	errno = 0;
	if (fseek(outfile, 0, SEEK_SET) != 0) {
		ERRS("fseek failed on output file");
		return ERR_FATAL;
	}

	switch (board->header_type) {
	case HEADER_TYPE_CAS:
		tmp.cas.type = HOST_TO_LE32(header.cas.type);
		tmp.cas.id = HOST_TO_LE32(header.cas.id);
		tmp.cas.kernel_offs = HOST_TO_LE32(sizeof(tmp.cas));
		tmp.cas.kernel_size = HOST_TO_LE32(kernel_image.out_size);
		tmp.cas.kernel_csum = HOST_TO_LE32(kernel_image.csum);
		tmp.cas.magic1 = HOST_TO_LE32(CAS_MAGIC1);
		tmp.cas.magic2 = HOST_TO_LE32(CAS_MAGIC2);
		tmp.cas.magic3 = HOST_TO_LE32(CAS_MAGIC3);
		res = write_out_data(outfile, (uint8_t *)&tmp.cas,
					sizeof(tmp.cas), NULL);
		break;
	case HEADER_TYPE_NFS:
		tmp.nfs.type = HOST_TO_LE32(header.nfs.type);
		tmp.nfs.id = HOST_TO_LE32(header.nfs.id);
		tmp.nfs.kernel_offs = HOST_TO_LE32(sizeof(tmp.nfs));
		tmp.nfs.kernel_size = HOST_TO_LE32(kernel_image.out_size);
		tmp.nfs.kernel_csum = HOST_TO_LE32(kernel_image.csum);
		tmp.nfs.fs_offs = HOST_TO_LE32(sizeof(tmp.nfs)
					+ kernel_image.out_size);
		tmp.nfs.fs_size = HOST_TO_LE32(fs_image.out_size);
		tmp.nfs.fs_csum = HOST_TO_LE32(fs_image.csum);
		res = write_out_data(outfile, (uint8_t *)&tmp.nfs,
					sizeof(tmp.nfs), NULL);
		break;
	}

	return res;
}