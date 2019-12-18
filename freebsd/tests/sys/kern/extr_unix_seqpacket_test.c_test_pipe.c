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
struct TYPE_2__ {size_t pktsize; int numpkts; int so; } ;
typedef  TYPE_1__ test_pipe_thread_data_t ;
typedef  int /*<<< orphan*/  sndbufsize ;
typedef  int /*<<< orphan*/  rcvbufsize ;
typedef  int /*<<< orphan*/  pthread_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE_EQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MAX (int,int) ; 
 int MIN (int,int) ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_RCVBUF ; 
 int /*<<< orphan*/  SO_SNDBUF ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  do_socketpair (int*) ; 
 int /*<<< orphan*/  pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  test_pipe_reader ; 
 int /*<<< orphan*/  test_pipe_writer ; 
 int /*<<< orphan*/  usleep (int) ; 

__attribute__((used)) static void
test_pipe(int sndbufsize, int rcvbufsize)
{
	test_pipe_thread_data_t writer_data, reader_data;
	pthread_t writer, reader;
	int sv[2];
	const size_t pktsize = MIN(sndbufsize, rcvbufsize) / 4;
	int numpkts;

	/* setup the socket pair */
	do_socketpair(sv);
	/* Setup the buffers */
	ATF_REQUIRE_EQ(0, setsockopt(sv[0], SOL_SOCKET, SO_SNDBUF, &sndbufsize,
	    sizeof(sndbufsize)));
	ATF_REQUIRE_EQ(0, setsockopt(sv[1], SOL_SOCKET, SO_RCVBUF, &rcvbufsize,
	    sizeof(rcvbufsize)));

	/* Send a total amount of data comfortably greater than the buffers */
	numpkts = MAX(sndbufsize, rcvbufsize) * 8 / pktsize;

	/* Start the child threads */
	writer_data.pktsize = pktsize;
	writer_data.numpkts = numpkts;
	writer_data.so = sv[0];
	reader_data.pktsize = pktsize;
	reader_data.numpkts = numpkts;
	reader_data.so = sv[1];
	ATF_REQUIRE_EQ(0, pthread_create(&writer, NULL, test_pipe_writer,
	    				 (void*)&writer_data));
	/*
	 * Give the writer time to start writing, and hopefully block, before
	 * starting the reader.  This increases the likelihood of the test case
	 * failing due to PR kern/185812
	 */
	usleep(1000);
	ATF_REQUIRE_EQ(0, pthread_create(&reader, NULL, test_pipe_reader,
	    				 (void*)&reader_data));

	/* Join the children */
	ATF_REQUIRE_EQ(0, pthread_join(writer, NULL));
	ATF_REQUIRE_EQ(0, pthread_join(reader, NULL));
	close(sv[0]);
	close(sv[1]);
}