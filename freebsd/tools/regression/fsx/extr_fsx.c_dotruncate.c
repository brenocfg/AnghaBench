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
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int /*<<< orphan*/  OP_TRUNCATE ; 
 unsigned int biggest ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  fd ; 
 unsigned int file_size ; 
 int ftruncate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ good_buf ; 
 int /*<<< orphan*/  log4 (int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (scalar_t__,char,int /*<<< orphan*/ ) ; 
 int monitorend ; 
 int monitorstart ; 
 int progressinterval ; 
 int /*<<< orphan*/  prt (char*,unsigned int,...) ; 
 int /*<<< orphan*/  prterr (char*) ; 
 int /*<<< orphan*/  quiet ; 
 int /*<<< orphan*/  report_failure (int) ; 
 int simulatedopcount ; 
 int testcalls ; 
 unsigned int truncbdy ; 

void
dotruncate(unsigned size)
{
	int oldsize = file_size;

	size -= size % truncbdy;
	if (size > biggest) {
		biggest = size;
		if (!quiet && testcalls > simulatedopcount)
			prt("truncating to largest ever: 0x%x\n", size);
	}

	log4(OP_TRUNCATE, size, (unsigned)file_size, 0);

	if (size > file_size)
		memset(good_buf + file_size, '\0', size - file_size);
	file_size = size;

	if (testcalls <= simulatedopcount)
		return;
	
	if ((progressinterval && testcalls % progressinterval == 0) ||
	    (debug && (monitorstart == -1 || monitorend == -1 ||
		       size <= monitorend)))
		prt("%lu trunc\tfrom 0x%x to 0x%x\n", testcalls, oldsize, size);
	if (ftruncate(fd, (off_t)size) == -1) {
		prt("ftruncate1: %x\n", size);
		prterr("dotruncate: ftruncate");
		report_failure(160);
	}
}