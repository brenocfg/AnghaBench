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
typedef  unsigned int off_t ;

/* Variables and functions */
 char* MAP_FAILED ; 
 int MAP_FILE ; 
 int MAP_SHARED ; 
 int /*<<< orphan*/  MS_SYNC ; 
 unsigned int OP_MAPWRITE ; 
 unsigned int OP_SKIPPED ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  check_eofpage (char*,unsigned int,char*,unsigned int) ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fd ; 
 unsigned int file_size ; 
 int ftruncate (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  gendata (int /*<<< orphan*/ ,scalar_t__,unsigned int,unsigned int) ; 
 scalar_t__ good_buf ; 
 scalar_t__ lite ; 
 int /*<<< orphan*/  log4 (unsigned int,unsigned int,unsigned int,unsigned int) ; 
 scalar_t__ mapped_msync ; 
 int /*<<< orphan*/  memcpy (char*,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  memset (scalar_t__,char,unsigned int) ; 
 scalar_t__ mmap (int /*<<< orphan*/ ,unsigned int,int,int,int /*<<< orphan*/ ,unsigned int) ; 
 int monitorend ; 
 int monitorstart ; 
 scalar_t__ msync (char*,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ munmap (char*,unsigned int) ; 
 int /*<<< orphan*/  original_buf ; 
 unsigned int page_mask ; 
 int progressinterval ; 
 int /*<<< orphan*/  prt (char*,...) ; 
 int /*<<< orphan*/  prterr (char*) ; 
 int /*<<< orphan*/  quiet ; 
 int /*<<< orphan*/  report_failure (int) ; 
 int simulatedopcount ; 
 int testcalls ; 
 int /*<<< orphan*/  warn (char*) ; 
 unsigned int writebdy ; 

void
domapwrite(unsigned offset, unsigned size)
{
	unsigned pg_offset;
	unsigned map_size;
	off_t    cur_filesize;
	char    *p;

	offset -= offset % writebdy;
	if (size == 0) {
		if (!quiet && testcalls > simulatedopcount)
			prt("skipping zero size write\n");
		log4(OP_SKIPPED, OP_MAPWRITE, offset, size);
		return;
	}
	cur_filesize = file_size;

	log4(OP_MAPWRITE, offset, size, 0);

	gendata(original_buf, good_buf, offset, size);
	if (file_size < offset + size) {
		if (file_size < offset)
			memset(good_buf + file_size, '\0', offset - file_size);
		file_size = offset + size;
		if (lite) {
			warn("Lite file size bug in fsx!");
			report_failure(200);
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
		prt("%lu mapwrite\t0x%x thru\t0x%x\t(0x%x bytes)\n", testcalls,
		    offset, offset + size - 1, size);

	if (file_size > cur_filesize) {
		if (ftruncate(fd, file_size) == -1) {
			prterr("domapwrite: ftruncate");
			exit(201);
		}
	}
	pg_offset = offset & page_mask;
	map_size  = pg_offset + size;

	if ((p = (char *)mmap(0, map_size, PROT_READ | PROT_WRITE,
			      MAP_FILE | MAP_SHARED, fd,
			      (off_t)(offset - pg_offset))) == MAP_FAILED) {
		prterr("domapwrite: mmap");
		report_failure(202);
	}
	memcpy(p + pg_offset, good_buf + offset, size);
	if (mapped_msync && msync(p, map_size, MS_SYNC) != 0) {
		prterr("domapwrite: msync");
		report_failure(203);
	}

	check_eofpage("Write", offset, p, size);

	if (munmap(p, map_size) != 0) {
		prterr("domapwrite: munmap");
		report_failure(204);
	}
}