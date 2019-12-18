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
typedef  int /*<<< orphan*/  io_buf ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 size_t const SIZE_MAX ; 
 scalar_t__ lseek (int,scalar_t__,int /*<<< orphan*/ ) ; 
 size_t read (int,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static bool
io_pread(int fd, io_buf *buf, size_t size, off_t pos)
{
	// Using lseek() and read() is more portable than pread() and
	// for us it is as good as real pread().
	if (lseek(fd, pos, SEEK_SET) != pos) {
		return true;
	}

	const size_t amount = read(fd, buf, size);
	if (amount == SIZE_MAX)
		return true;

	if (amount != size) {
		return true;
	}

	return false;
}