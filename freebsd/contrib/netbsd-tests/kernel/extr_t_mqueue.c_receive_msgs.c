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
struct mq_attr {int mq_msgsize; } ;
typedef  int /*<<< orphan*/  mqd_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE_MSG (int,char*,...) ; 
 int MQ_PRIO_BASE ; 
 char* calloc (int,int) ; 
 int /*<<< orphan*/  errno ; 
 int mq_getattr (int /*<<< orphan*/ ,struct mq_attr*) ; 
 int mq_receive (int /*<<< orphan*/ ,char*,int,unsigned int*) ; 

__attribute__((used)) static void
receive_msgs(mqd_t mqfd)
{
	struct mq_attr mqa;
	char *m;
	unsigned p;
	int len;

	ATF_REQUIRE_MSG(mq_getattr(mqfd, &mqa) != -1, "mq_getattr failed %d",
	    errno);

	len = mqa.mq_msgsize;
	m = calloc(1, len);
	ATF_REQUIRE_MSG(m != NULL, "calloc failed");

	ATF_REQUIRE_MSG(mq_receive(mqfd, m, len, &p) != -1,
	    "mq_receive 1 failed: %d", errno);
	ATF_REQUIRE_MSG(p == (MQ_PRIO_BASE + 1) && m[0] == 'b',
	    "mq_receive 1 prio/data mismatch");

	ATF_REQUIRE_MSG(mq_receive(mqfd, m, len, &p) != -1,
	    "mq_receive 2 failed: %d", errno);
	ATF_REQUIRE_MSG(p == (MQ_PRIO_BASE + 1) && m[0] == 'f',
	    "mq_receive 2 prio/data mismatch");

	ATF_REQUIRE_MSG(mq_receive(mqfd, m, len, &p) != -1,
	    "mq_receive 3 failed: %d", errno);
	ATF_REQUIRE_MSG(p == MQ_PRIO_BASE && m[0] == 'a',
	    "mq_receive 3 prio/data mismatch");

	ATF_REQUIRE_MSG(mq_receive(mqfd, m, len, &p) != -1,
	    "mq_receive 4 failed: %d", errno);
	ATF_REQUIRE_MSG(p == MQ_PRIO_BASE && m[0] == 'c',
	    "mq_receive 4 prio/data mismatch");

	ATF_REQUIRE_MSG(mq_receive(mqfd, m, len, &p) != -1,
	    "mq_receive 5 failed: %d", errno);
	ATF_REQUIRE_MSG(p == (MQ_PRIO_BASE - 1) && m[0] == 'd',
	    "mq_receive 5 prio/data mismatch");

	ATF_REQUIRE_MSG(mq_receive(mqfd, m, len, &p) != -1,
	    "mq_receive 6 failed: %d", errno);
	ATF_REQUIRE_MSG(p == 0 && m[0] == 'e',
	    "mq_receive 6 prio/data mismatch");
}