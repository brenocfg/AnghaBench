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
struct info_control {int /*<<< orphan*/  numctlbadop; int /*<<< orphan*/  numctldatatooshort; int /*<<< orphan*/  numctlbadversion; int /*<<< orphan*/  numctlbadoffset; int /*<<< orphan*/  numctlinputerr; int /*<<< orphan*/  numctlinputfrag; int /*<<< orphan*/  numctlinputresp; int /*<<< orphan*/  numctltooshort; int /*<<< orphan*/  numctlbadpkts; int /*<<< orphan*/  numctlerrors; int /*<<< orphan*/  numasyncmsgs; int /*<<< orphan*/  numctlfrags; int /*<<< orphan*/  numctlresponses; int /*<<< orphan*/  numctlreq; int /*<<< orphan*/  ctltimereset; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ IMPL_XNTPD ; 
 scalar_t__ IMPL_XNTPD_OLD ; 
 int INFO_ERR_IMPL ; 
 int /*<<< orphan*/  REQ_GET_CTLSTATS ; 
 int /*<<< orphan*/  check1item (size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  checkitemsize (size_t,int) ; 
 int doquery (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t*,size_t*,void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ impl_ver ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ctlstats(
	struct parse *pcmd,
	FILE *fp
	)
{
	struct info_control *ic;
	size_t items;
	size_t itemsize;
	int res;

again:
	res = doquery(impl_ver, REQ_GET_CTLSTATS, 0, 0, 0, NULL, &items,
		      &itemsize, (void *)&ic, 0, sizeof(*ic));
	
	if (res == INFO_ERR_IMPL && impl_ver == IMPL_XNTPD) {
		impl_ver = IMPL_XNTPD_OLD;
		goto again;
	}

	if (res != 0)
		return;

	if (!check1item(items, fp))
		return;

	if (!checkitemsize(itemsize, sizeof(*ic)))
		return;

	fprintf(fp, "time since reset:       %lu\n",
		(u_long)ntohl(ic->ctltimereset));
	fprintf(fp, "requests received:      %lu\n",
		(u_long)ntohl(ic->numctlreq));
	fprintf(fp, "responses sent:         %lu\n",
		(u_long)ntohl(ic->numctlresponses));
	fprintf(fp, "fragments sent:         %lu\n",
		(u_long)ntohl(ic->numctlfrags));
	fprintf(fp, "async messages sent:    %lu\n",
		(u_long)ntohl(ic->numasyncmsgs));
	fprintf(fp, "error msgs sent:        %lu\n",
		(u_long)ntohl(ic->numctlerrors));
	fprintf(fp, "total bad pkts:         %lu\n",
		(u_long)ntohl(ic->numctlbadpkts));
	fprintf(fp, "packet too short:       %lu\n",
		(u_long)ntohl(ic->numctltooshort));
	fprintf(fp, "response on input:      %lu\n",
		(u_long)ntohl(ic->numctlinputresp));
	fprintf(fp, "fragment on input:      %lu\n",
		(u_long)ntohl(ic->numctlinputfrag));
	fprintf(fp, "error set on input:     %lu\n",
		(u_long)ntohl(ic->numctlinputerr));
	fprintf(fp, "bad offset on input:    %lu\n",
		(u_long)ntohl(ic->numctlbadoffset));
	fprintf(fp, "bad version packets:    %lu\n",
		(u_long)ntohl(ic->numctlbadversion));
	fprintf(fp, "data in pkt too short:  %lu\n",
		(u_long)ntohl(ic->numctldatatooshort));
	fprintf(fp, "unknown op codes:       %lu\n",
		(u_long)ntohl(ic->numctlbadop));
}