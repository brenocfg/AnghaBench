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
typedef  int u_long ;
typedef  int u_int ;
struct parse {int dummy; } ;
struct info_io_stats {int /*<<< orphan*/  int_received; int /*<<< orphan*/  interrupts; int /*<<< orphan*/  notsent; int /*<<< orphan*/  sent; int /*<<< orphan*/  received; int /*<<< orphan*/  ignored; int /*<<< orphan*/  dropped; int /*<<< orphan*/  lowwater; int /*<<< orphan*/  fullrecvbufs; int /*<<< orphan*/  freerecvbufs; int /*<<< orphan*/  totalrecvbufs; int /*<<< orphan*/  timereset; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ IMPL_XNTPD ; 
 scalar_t__ IMPL_XNTPD_OLD ; 
 int INFO_ERR_IMPL ; 
 int /*<<< orphan*/  REQ_IO_STATS ; 
 int /*<<< orphan*/  check1item (size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  checkitemsize (size_t,int) ; 
 int doquery (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t*,size_t*,void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ impl_ver ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
iostats(
	struct parse *pcmd,
	FILE *fp
	)
{
	struct info_io_stats *io;
	size_t items;
	size_t itemsize;
	int res;

again:
	res = doquery(impl_ver, REQ_IO_STATS, 0, 0, 0, NULL, &items,
		      &itemsize, (void *)&io, 0, sizeof(*io));
	
	if (res == INFO_ERR_IMPL && impl_ver == IMPL_XNTPD) {
		impl_ver = IMPL_XNTPD_OLD;
		goto again;
	}

	if (res != 0)
		return;

	if (!check1item(items, fp))
		return;

	if (!checkitemsize(itemsize, sizeof(*io)))
		return;

	fprintf(fp, "time since reset:     %lu\n",
		(u_long)ntohl(io->timereset));
	fprintf(fp, "receive buffers:      %u\n",
		(u_int)ntohs(io->totalrecvbufs));
	fprintf(fp, "free receive buffers: %u\n",
		(u_int)ntohs(io->freerecvbufs));
	fprintf(fp, "used receive buffers: %u\n",
		(u_int)ntohs(io->fullrecvbufs));
	fprintf(fp, "low water refills:    %u\n",
		(u_int)ntohs(io->lowwater));
	fprintf(fp, "dropped packets:      %lu\n",
		(u_long)ntohl(io->dropped));
	fprintf(fp, "ignored packets:      %lu\n",
		(u_long)ntohl(io->ignored));
	fprintf(fp, "received packets:     %lu\n",
		(u_long)ntohl(io->received));
	fprintf(fp, "packets sent:         %lu\n",
		(u_long)ntohl(io->sent));
	fprintf(fp, "packets not sent:     %lu\n",
		(u_long)ntohl(io->notsent));
	fprintf(fp, "interrupts handled:   %lu\n",
		(u_long)ntohl(io->interrupts));
	fprintf(fp, "received by int:      %lu\n",
		(u_long)ntohl(io->int_received));
}