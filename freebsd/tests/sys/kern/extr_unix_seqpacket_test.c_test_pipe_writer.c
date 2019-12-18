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
 int /*<<< orphan*/  ATF_CHECK_EQ_MSG (int,scalar_t__,char*,int,scalar_t__) ; 
 int /*<<< orphan*/  MSG_EOR ; 
 int /*<<< orphan*/  atf_tc_fail (char*) ; 
 int /*<<< orphan*/  memset (char*,int,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ send (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void*
test_pipe_writer(void* args)
{
	test_pipe_thread_data_t* td = args;
	char sndbuf[td->pktsize];
	ssize_t ssize;
	int i;

	for(i=0; i < td->numpkts; i++) {
			memset(sndbuf, i, td->pktsize);
			ssize = send(td->so, sndbuf, td->pktsize, MSG_EOR);
			if (ssize < 0) {
				perror("send");
				atf_tc_fail("send returned < 0");
			}
			ATF_CHECK_EQ_MSG(td->pktsize, ssize,
			    		 "expected %zd=send(...) but got %zd",
			    		  td->pktsize, ssize);
	}
	return (0);
}