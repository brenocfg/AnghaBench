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
typedef  union u_spcl {int dummy; } u_spcl ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  ino_t ;
struct TYPE_2__ {int c_checksum; int /*<<< orphan*/  c_magic; int /*<<< orphan*/  c_inumber; int /*<<< orphan*/  c_mtimensec; int /*<<< orphan*/  c_atimensec; int /*<<< orphan*/  c_mtime; int /*<<< orphan*/  c_atime; } ;

/* Variables and functions */
 int CHECKSUM ; 
 int /*<<< orphan*/  FS_UFS2_MAGIC ; 
 int rsync_friendly ; 
 TYPE_1__ spcl ; 
 int /*<<< orphan*/  writerec (char*,int) ; 

void
writeheader(ino_t ino)
{
	int32_t sum, cnt, *lp;

	if (rsync_friendly >= 2) {
		/* don't track changes to access time */
		spcl.c_atime = spcl.c_mtime;
		spcl.c_atimensec = spcl.c_mtimensec;
	}
	spcl.c_inumber = ino;
	spcl.c_magic = FS_UFS2_MAGIC;
	spcl.c_checksum = 0;
	lp = (int32_t *)&spcl;
	sum = 0;
	cnt = sizeof(union u_spcl) / (4 * sizeof(int32_t));
	while (--cnt >= 0) {
		sum += *lp++;
		sum += *lp++;
		sum += *lp++;
		sum += *lp++;
	}
	spcl.c_checksum = CHECKSUM - sum;
	writerec((char *)&spcl, 1);
}