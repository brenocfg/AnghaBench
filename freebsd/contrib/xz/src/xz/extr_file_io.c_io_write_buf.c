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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int ssize_t ;
struct TYPE_4__ {int /*<<< orphan*/  dest_name; int /*<<< orphan*/  dest_fd; } ;
typedef  TYPE_1__ file_pair ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 scalar_t__ EPIPE ; 
 scalar_t__ IO_WAIT_MORE ; 
 scalar_t__ IS_EAGAIN_OR_EWOULDBLOCK (scalar_t__) ; 
 size_t SSIZE_MAX ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ errno ; 
 scalar_t__ io_wait (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  message_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 scalar_t__ user_abort ; 
 int write (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static bool
io_write_buf(file_pair *pair, const uint8_t *buf, size_t size)
{
	assert(size < SSIZE_MAX);

	while (size > 0) {
		const ssize_t amount = write(pair->dest_fd, buf, size);
		if (amount == -1) {
			if (errno == EINTR) {
				if (user_abort)
					return true;

				continue;
			}

#ifndef TUKLIB_DOSLIKE
			if (IS_EAGAIN_OR_EWOULDBLOCK(errno)) {
				if (io_wait(pair, -1, false) == IO_WAIT_MORE)
					continue;

				return true;
			}
#endif

			// Handle broken pipe specially. gzip and bzip2
			// don't print anything on SIGPIPE. In addition,
			// gzip --quiet uses exit status 2 (warning) on
			// broken pipe instead of whatever raise(SIGPIPE)
			// would make it return. It is there to hide "Broken
			// pipe" message on some old shells (probably old
			// GNU bash).
			//
			// We don't do anything special with --quiet, which
			// is what bzip2 does too. If we get SIGPIPE, we
			// will handle it like other signals by setting
			// user_abort, and get EPIPE here.
			if (errno != EPIPE)
				message_error(_("%s: Write error: %s"),
					pair->dest_name, strerror(errno));

			return true;
		}

		buf += (size_t)(amount);
		size -= (size_t)(amount);
	}

	return false;
}