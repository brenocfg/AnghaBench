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
struct rusage {scalar_t__ ru_msgsnd; scalar_t__ ru_msgrcv; } ;
struct aio_context {int dummy; } ;
typedef  int /*<<< orphan*/  completion ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE (int) ; 
 int /*<<< orphan*/  ATF_REQUIRE_KERNEL_MODULE (char*) ; 
 int /*<<< orphan*/  ATF_REQUIRE_MSG (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PF_UNIX ; 
 int /*<<< orphan*/  RUSAGE_SELF ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  UNIX_SOCKETPAIR_LEN ; 
 int /*<<< orphan*/  aio_context_init (struct aio_context*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aio_read_test (struct aio_context*,int /*<<< orphan*/ ,struct sigevent*) ; 
 int /*<<< orphan*/  aio_write_test (struct aio_context*,int /*<<< orphan*/ ,struct sigevent*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int getrusage (int /*<<< orphan*/ ,struct rusage*) ; 
 int socketpair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
aio_unix_socketpair_test(completion comp, struct sigevent *sev)
{
	struct aio_context ac;
	struct rusage ru_before, ru_after;
	int sockets[2];

	ATF_REQUIRE_KERNEL_MODULE("aio");

	ATF_REQUIRE_MSG(socketpair(PF_UNIX, SOCK_STREAM, 0, sockets) != -1,
	    "socketpair failed: %s", strerror(errno));

	aio_context_init(&ac, sockets[0], sockets[1], UNIX_SOCKETPAIR_LEN);
	ATF_REQUIRE_MSG(getrusage(RUSAGE_SELF, &ru_before) != -1,
	    "getrusage failed: %s", strerror(errno));
	aio_write_test(&ac, comp, sev);
	ATF_REQUIRE_MSG(getrusage(RUSAGE_SELF, &ru_after) != -1,
	    "getrusage failed: %s", strerror(errno));
	ATF_REQUIRE(ru_after.ru_msgsnd == ru_before.ru_msgsnd + 1);
	ru_before = ru_after;
	aio_read_test(&ac, comp, sev);
	ATF_REQUIRE_MSG(getrusage(RUSAGE_SELF, &ru_after) != -1,
	    "getrusage failed: %s", strerror(errno));
	ATF_REQUIRE(ru_after.ru_msgrcv == ru_before.ru_msgrcv + 1);

	close(sockets[0]);
	close(sockets[1]);
}