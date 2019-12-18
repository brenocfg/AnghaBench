#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ off_t ;

/* Variables and functions */
 unsigned int OP_SKIPPED ; 
 unsigned int OP_WRITE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  fd ; 
 unsigned int file_size ; 
 int /*<<< orphan*/  gendata (int /*<<< orphan*/ ,scalar_t__,unsigned int,unsigned int) ; 
 scalar_t__ good_buf ; 
 scalar_t__ lite ; 
 int /*<<< orphan*/  log4 (unsigned int,unsigned int,unsigned int,unsigned int) ; 
 scalar_t__ lseek (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (scalar_t__,char,unsigned int) ; 
 int monitorend ; 
 int monitorstart ; 
 int /*<<< orphan*/  original_buf ; 
 int progressinterval ; 
 int /*<<< orphan*/  prt (char*,...) ; 
 int /*<<< orphan*/  prterr (char*) ; 
 int /*<<< orphan*/  quiet ; 
 int /*<<< orphan*/  report_failure (int) ; 
 int simulatedopcount ; 
 int testcalls ; 
 int /*<<< orphan*/  warn (char*) ; 
 unsigned int write (int /*<<< orphan*/ ,scalar_t__,unsigned int) ; 
 unsigned int writebdy ; 

void
dowrite(unsigned offset, unsigned size)
{
	off_t ret;
	unsigned iret;

	offset -= offset % writebdy;
	if (size == 0) {
		if (!quiet && testcalls > simulatedopcount)
			prt("skipping zero size write\n");
		log4(OP_SKIPPED, OP_WRITE, offset, size);
		return;
	}

	log4(OP_WRITE, offset, size, file_size);

	gendata(original_buf, good_buf, offset, size);
	if (file_size < offset + size) {
		if (file_size < offset)
			memset(good_buf + file_size, '\0', offset - file_size);
		file_size = offset + size;
		if (lite) {
			warn("Lite file size bug in fsx!");
			report_failure(149);
		}
	}

	if (testcalls <= simulatedopcount)
		return;

	if (!quiet && ((progressinterval &&
			testcalls % progressinterval == 0) ||
		       (debug &&
			(monitorstart == -1 ||
			 (offset + size > monitorstart &&
			  (monitorend == -1 || offset <= monitorend))))))
		prt("%lu write\t0x%x thru\t0x%x\t(0x%x bytes)\n", testcalls,
		    offset, offset + size - 1, size);
	ret = lseek(fd, (off_t)offset, SEEK_SET);
	if (ret == (off_t)-1) {
		prterr("dowrite: lseek");
		report_failure(150);
	}
	iret = write(fd, good_buf + offset, size);
	if (iret != size) {
		if (iret == -1)
			prterr("dowrite: write");
		else
			prt("short write: 0x%x bytes instead of 0x%x\n",
			    iret, size);
		report_failure(151);
	}
}