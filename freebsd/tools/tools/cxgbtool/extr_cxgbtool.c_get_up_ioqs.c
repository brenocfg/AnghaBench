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
struct t3_ioq_entry {int dummy; } ;
struct ch_up_ioqs {int bufsize; int ioq_rx_enable; int ioq_tx_enable; int ioq_rx_status; int ioq_tx_status; TYPE_1__* data; } ;
typedef  int /*<<< orphan*/  ioqs ;
struct TYPE_2__ {int ioq_cp; int ioq_pp; int ioq_alen; int ioq_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHELSIO_GET_UP_IOQS ; 
 int IOQS_BUFSIZE ; 
 int /*<<< orphan*/  bzero (struct ch_up_ioqs*,int) ; 
 scalar_t__ doit (char const*,int /*<<< orphan*/ ,struct ch_up_ioqs*) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 

__attribute__((used)) static int
get_up_ioqs(int argc, char *argv[], int start_arg, const char *iff_name)
{
	struct ch_up_ioqs ioqs;
	int i, entries;

	(void) argc;
	(void) argv;
	(void) start_arg;

	bzero(&ioqs, sizeof(ioqs));
	ioqs.bufsize = IOQS_BUFSIZE;
	ioqs.data = malloc(IOQS_BUFSIZE);
	if (!ioqs.data)
		err(1, "uP_IOQs malloc");

	if (doit(iff_name, CHELSIO_GET_UP_IOQS, &ioqs) < 0)
		 err(1, "uP_IOQs");

	printf("ioq_rx_enable   : 0x%08x\n", ioqs.ioq_rx_enable);
	printf("ioq_tx_enable   : 0x%08x\n", ioqs.ioq_tx_enable);
	printf("ioq_rx_status   : 0x%08x\n", ioqs.ioq_rx_status);
	printf("ioq_tx_status   : 0x%08x\n", ioqs.ioq_tx_status);
	
	entries = ioqs.bufsize / sizeof(struct t3_ioq_entry);
	for (i = 0; i < entries; i++) {
		printf("\nioq[%d].cp       : 0x%08x\n", i,
		       ioqs.data[i].ioq_cp);
		printf("ioq[%d].pp       : 0x%08x\n", i,
		       ioqs.data[i].ioq_pp);
		printf("ioq[%d].alen     : 0x%08x\n", i,
		       ioqs.data[i].ioq_alen);
		printf("ioq[%d].stats    : 0x%08x\n", i,
		       ioqs.data[i].ioq_stats);
		printf("  sop %u\n", ioqs.data[i].ioq_stats >> 16);
		printf("  eop %u\n", ioqs.data[i].ioq_stats  & 0xFFFF);
	}

	return 0;
}