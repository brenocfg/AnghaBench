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
typedef  int ssize_t ;
typedef  scalar_t__ off_t ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  fd ; 
 scalar_t__ file_size ; 
 int ftruncate (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  good_buf ; 
 scalar_t__ lite ; 
 scalar_t__ lseek (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prt (char*,unsigned long long,...) ; 
 int /*<<< orphan*/  prterr (char*) ; 
 int /*<<< orphan*/  report_failure (int) ; 
 int write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

void
writefileimage()
{
	ssize_t iret;

	if (lseek(fd, (off_t)0, SEEK_SET) == (off_t)-1) {
		prterr("writefileimage: lseek");
		report_failure(171);
	}
	iret = write(fd, good_buf, file_size);
	if ((off_t)iret != file_size) {
		if (iret == -1)
			prterr("writefileimage: write");
		else
			prt("short write: 0x%x bytes instead of 0x%llx\n",
			    iret, (unsigned long long)file_size);
		report_failure(172);
	}
	if (lite ? 0 : ftruncate(fd, file_size) == -1) {
		prt("ftruncate2: %llx\n", (unsigned long long)file_size);
		prterr("writefileimage: ftruncate");
		report_failure(173);
	}
}