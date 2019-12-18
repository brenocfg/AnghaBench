#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ off_t ;
typedef  int /*<<< orphan*/  io_buf ;
struct TYPE_4__ {int /*<<< orphan*/  src_name; int /*<<< orphan*/  src_fd; } ;
typedef  TYPE_1__ file_pair ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 size_t const SIZE_MAX ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  errno ; 
 size_t io_read (TYPE_1__*,int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ lseek (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  message_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

extern bool
io_pread(file_pair *pair, io_buf *buf, size_t size, off_t pos)
{
	// Using lseek() and read() is more portable than pread() and
	// for us it is as good as real pread().
	if (lseek(pair->src_fd, pos, SEEK_SET) != pos) {
		message_error(_("%s: Error seeking the file: %s"),
				pair->src_name, strerror(errno));
		return true;
	}

	const size_t amount = io_read(pair, buf, size);
	if (amount == SIZE_MAX)
		return true;

	if (amount != size) {
		message_error(_("%s: Unexpected end of file"),
				pair->src_name);
		return true;
	}

	return false;
}