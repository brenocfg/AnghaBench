#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int pktsize; int numpkts; int /*<<< orphan*/  so; } ;
typedef  TYPE_1__ test_pipe_thread_data_t ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_CHECK_EQ_MSG (int,int,char*,int,...) ; 
 int /*<<< orphan*/  MSG_WAITALL ; 
 int /*<<< orphan*/  atf_tc_fail (char*) ; 
 int memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ recv (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void*
test_pipe_reader(void* args)
{
	test_pipe_thread_data_t* td = args;
	char rcvbuf[td->pktsize];
	char comparebuf[td->pktsize];
	ssize_t rsize;
	int i, d;

	for(i=0; i < td->numpkts; i++) {
		memset(comparebuf, i, td->pktsize);
		rsize = recv(td->so, rcvbuf, td->pktsize, MSG_WAITALL);
		if (rsize < 0) {
			perror("recv");
			atf_tc_fail("recv returned < 0");
		}
		ATF_CHECK_EQ_MSG(td->pktsize, rsize,
		    		 "expected %zd=send(...) but got %zd",
				 td->pktsize, rsize);
		d = memcmp(comparebuf, rcvbuf, td->pktsize);
		ATF_CHECK_EQ_MSG(0, d,
		    		 "Received data miscompare on packet %d", i);
	}
	return (0);
}