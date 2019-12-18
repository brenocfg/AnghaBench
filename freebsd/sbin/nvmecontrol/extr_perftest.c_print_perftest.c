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
typedef  int uintmax_t ;
typedef  int uint64_t ;
typedef  size_t uint32_t ;
struct nvme_io_test {size_t num_threads; int time; int size; scalar_t__ opc; scalar_t__* io_completed; } ;

/* Variables and functions */
 scalar_t__ NVME_OPC_READ ; 
 int /*<<< orphan*/  printf (char*,size_t,int,...) ; 

__attribute__((used)) static void
print_perftest(struct nvme_io_test *io_test, bool perthread)
{
	uint64_t	io_completed = 0, iops, mbps;
	uint32_t	i;

	for (i = 0; i < io_test->num_threads; i++)
		io_completed += io_test->io_completed[i];

	iops = io_completed/io_test->time;
	mbps = iops * io_test->size / (1024*1024);

	printf("Threads: %2d Size: %6d %5s Time: %3d IO/s: %7ju MB/s: %4ju\n",
	    io_test->num_threads, io_test->size,
	    io_test->opc == NVME_OPC_READ ? "READ" : "WRITE",
	    io_test->time, (uintmax_t)iops, (uintmax_t)mbps);

	if (perthread)
		for (i = 0; i < io_test->num_threads; i++)
			printf("\t%3d: %8ju IO/s\n", i,
			    (uintmax_t)io_test->io_completed[i]/io_test->time);
}