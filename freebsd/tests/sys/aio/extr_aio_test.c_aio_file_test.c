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
struct sigevent {int dummy; } ;
struct aio_context {int dummy; } ;
typedef  int /*<<< orphan*/  completion ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE_KERNEL_MODULE (char*) ; 
 int /*<<< orphan*/  ATF_REQUIRE_MSG (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATF_REQUIRE_UNSAFE_AIO () ; 
 int /*<<< orphan*/  FILE_LEN ; 
 int /*<<< orphan*/  FILE_PATHNAME ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int /*<<< orphan*/  aio_context_init (struct aio_context*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aio_read_test (struct aio_context*,int /*<<< orphan*/ ,struct sigevent*) ; 
 int /*<<< orphan*/  aio_write_test (struct aio_context*,int /*<<< orphan*/ ,struct sigevent*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int open (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
aio_file_test(completion comp, struct sigevent *sev)
{
	struct aio_context ac;
	int fd;

	ATF_REQUIRE_KERNEL_MODULE("aio");
	ATF_REQUIRE_UNSAFE_AIO();

	fd = open(FILE_PATHNAME, O_RDWR | O_CREAT, 0600);
	ATF_REQUIRE_MSG(fd != -1, "open failed: %s", strerror(errno));

	aio_context_init(&ac, fd, fd, FILE_LEN);
	aio_write_test(&ac, comp, sev);
	aio_read_test(&ac, comp, sev);
	close(fd);
}