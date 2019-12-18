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
 int /*<<< orphan*/  PIPE_LEN ; 
 int /*<<< orphan*/  aio_context_init (struct aio_context*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aio_read_test (struct aio_context*,int /*<<< orphan*/ ,struct sigevent*) ; 
 int /*<<< orphan*/  aio_write_test (struct aio_context*,int /*<<< orphan*/ ,struct sigevent*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int pipe (int*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
aio_pipe_test(completion comp, struct sigevent *sev)
{
	struct aio_context ac;
	int pipes[2];

	ATF_REQUIRE_KERNEL_MODULE("aio");
	ATF_REQUIRE_UNSAFE_AIO();

	ATF_REQUIRE_MSG(pipe(pipes) != -1,
	    "pipe failed: %s", strerror(errno));

	aio_context_init(&ac, pipes[0], pipes[1], PIPE_LEN);
	aio_write_test(&ac, comp, sev);
	aio_read_test(&ac, comp, sev);

	close(pipes[0]);
	close(pipes[1]);
}