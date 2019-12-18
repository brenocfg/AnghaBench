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
typedef  int /*<<< orphan*/  u_long ;
typedef  int u_int ;
struct parse {int dummy; } ;
struct info_mem_stats {scalar_t__* hashcount; int /*<<< orphan*/  demobilizations; int /*<<< orphan*/  allocations; int /*<<< orphan*/  findpeer_calls; int /*<<< orphan*/  freepeermem; int /*<<< orphan*/  totalpeermem; int /*<<< orphan*/  timereset; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ IMPL_XNTPD ; 
 scalar_t__ IMPL_XNTPD_OLD ; 
 int INFO_ERR_IMPL ; 
 int NTP_HASH_SIZE ; 
 int /*<<< orphan*/  REQ_MEM_STATS ; 
 int /*<<< orphan*/  check1item (size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  checkitemsize (size_t,int) ; 
 int doquery (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t*,size_t*,void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ impl_ver ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
memstats(
	struct parse *pcmd,
	FILE *fp
	)
{
	struct info_mem_stats *mem;
	int i;
	size_t items;
	size_t itemsize;
	int res;

again:
	res = doquery(impl_ver, REQ_MEM_STATS, 0, 0, 0, NULL, &items,
		      &itemsize, (void *)&mem, 0, sizeof(*mem));
	
	if (res == INFO_ERR_IMPL && impl_ver == IMPL_XNTPD) {
		impl_ver = IMPL_XNTPD_OLD;
		goto again;
	}

	if (res != 0)
		return;

	if (!check1item(items, fp))
		return;

	if (!checkitemsize(itemsize, sizeof(*mem)))
		return;

	fprintf(fp, "time since reset:     %lu\n",
		(u_long)ntohl(mem->timereset));
	fprintf(fp, "total peer memory:    %u\n",
		(u_int)ntohs(mem->totalpeermem));
	fprintf(fp, "free peer memory:     %u\n",
		(u_int)ntohs(mem->freepeermem));
	fprintf(fp, "calls to findpeer:    %lu\n",
		(u_long)ntohl(mem->findpeer_calls));
	fprintf(fp, "new peer allocations: %lu\n",
		(u_long)ntohl(mem->allocations));
	fprintf(fp, "peer demobilizations: %lu\n",
		(u_long)ntohl(mem->demobilizations));

	fprintf(fp, "hash table counts:   ");
	for (i = 0; i < NTP_HASH_SIZE; i++) {
		fprintf(fp, "%4d", (int)mem->hashcount[i]);
		if ((i % 8) == 7 && i != (NTP_HASH_SIZE-1))
			fprintf(fp, "\n                     ");
	}
	fprintf(fp, "\n");
}