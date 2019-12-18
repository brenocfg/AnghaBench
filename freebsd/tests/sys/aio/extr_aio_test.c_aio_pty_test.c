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
struct termios {int dummy; } ;
struct sigevent {int dummy; } ;
struct aio_context {int dummy; } ;
typedef  int /*<<< orphan*/  completion ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE_KERNEL_MODULE (char*) ; 
 int /*<<< orphan*/  ATF_REQUIRE_MSG (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATF_REQUIRE_UNSAFE_AIO () ; 
 int /*<<< orphan*/  PTY_LEN ; 
 int /*<<< orphan*/  TCSANOW ; 
 int /*<<< orphan*/  aio_context_init (struct aio_context*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aio_read_test (struct aio_context*,int /*<<< orphan*/ ,struct sigevent*) ; 
 int /*<<< orphan*/  aio_write_test (struct aio_context*,int /*<<< orphan*/ ,struct sigevent*) ; 
 int /*<<< orphan*/  atf_tc_fail (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfmakeraw (struct termios*) ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 scalar_t__ openpty (int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strerror (int) ; 
 scalar_t__ tcgetattr (int,struct termios*) ; 
 scalar_t__ tcsetattr (int,int /*<<< orphan*/ ,struct termios*) ; 

__attribute__((used)) static void
aio_pty_test(completion comp, struct sigevent *sev)
{
	struct aio_context ac;
	int read_fd, write_fd;
	struct termios ts;
	int error;

	ATF_REQUIRE_KERNEL_MODULE("aio");
	ATF_REQUIRE_UNSAFE_AIO();

	ATF_REQUIRE_MSG(openpty(&read_fd, &write_fd, NULL, NULL, NULL) == 0,
	    "openpty failed: %s", strerror(errno));


	if (tcgetattr(write_fd, &ts) < 0) {
		error = errno;
		errno = error;
		atf_tc_fail("tcgetattr failed: %s", strerror(errno));
	}
	cfmakeraw(&ts);
	if (tcsetattr(write_fd, TCSANOW, &ts) < 0) {
		error = errno;
		errno = error;
		atf_tc_fail("tcsetattr failed: %s", strerror(errno));
	}
	aio_context_init(&ac, read_fd, write_fd, PTY_LEN);

	aio_write_test(&ac, comp, sev);
	aio_read_test(&ac, comp, sev);

	close(read_fd);
	close(write_fd);
}