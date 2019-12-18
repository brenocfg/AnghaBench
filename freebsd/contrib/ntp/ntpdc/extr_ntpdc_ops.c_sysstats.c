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
struct parse {int dummy; } ;
struct old_info_sys_stats {int dummy; } ;
struct info_sys_stats {int /*<<< orphan*/  limitrejected; int /*<<< orphan*/  badauth; int /*<<< orphan*/  badlength; int /*<<< orphan*/  denied; int /*<<< orphan*/  unknownversion; int /*<<< orphan*/  oldversionpkt; int /*<<< orphan*/  newversionpkt; int /*<<< orphan*/  processed; int /*<<< orphan*/  received; int /*<<< orphan*/  timereset; int /*<<< orphan*/  timeup; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ IMPL_XNTPD ; 
 scalar_t__ IMPL_XNTPD_OLD ; 
 int INFO_ERR_IMPL ; 
 int /*<<< orphan*/  REQ_SYS_STATS ; 
 int /*<<< orphan*/  check1item (size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  checkitemsize (size_t,int) ; 
 int doquery (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t*,size_t*,void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ impl_ver ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sysstats(
	struct parse *pcmd,
	FILE *fp
	)
{
	struct info_sys_stats *ss;
	size_t items;
	size_t itemsize;
	int res;

again:
	res = doquery(impl_ver, REQ_SYS_STATS, 0, 0, 0, (char *)NULL,
		      &items, &itemsize, (void *)&ss, 0, 
		      sizeof(struct info_sys_stats));
	
	if (res == INFO_ERR_IMPL && impl_ver == IMPL_XNTPD) {
		impl_ver = IMPL_XNTPD_OLD;
		goto again;
	}

	if (res != 0)
	    return;

	if (!check1item(items, fp))
	    return;

	if (itemsize != sizeof(struct info_sys_stats) &&
	    itemsize != sizeof(struct old_info_sys_stats)) {
		/* issue warning according to new structure size */
		checkitemsize(itemsize, sizeof(struct info_sys_stats));
		return;
	}
	fprintf(fp, "time since restart:     %lu\n",
		(u_long)ntohl(ss->timeup));
	fprintf(fp, "time since reset:       %lu\n",
		(u_long)ntohl(ss->timereset));
	fprintf(fp, "packets received:       %lu\n",
		(u_long)ntohl(ss->received));
	fprintf(fp, "packets processed:      %lu\n",
		(u_long)ntohl(ss->processed));
	fprintf(fp, "current version:        %lu\n",
		(u_long)ntohl(ss->newversionpkt));
	fprintf(fp, "previous version:       %lu\n",
		(u_long)ntohl(ss->oldversionpkt));
	fprintf(fp, "declined:               %lu\n",
		(u_long)ntohl(ss->unknownversion));
	fprintf(fp, "access denied:          %lu\n",
		(u_long)ntohl(ss->denied));
	fprintf(fp, "bad length or format:   %lu\n",
		(u_long)ntohl(ss->badlength));
	fprintf(fp, "bad authentication:     %lu\n",
		(u_long)ntohl(ss->badauth));
	if (itemsize != sizeof(struct info_sys_stats))
	    return;
	
	fprintf(fp, "rate exceeded:          %lu\n",
	       (u_long)ntohl(ss->limitrejected));
}