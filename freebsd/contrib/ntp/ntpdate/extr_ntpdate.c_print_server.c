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
struct sockaddr_in {int /*<<< orphan*/  sin_port; } ;
struct server {scalar_t__ stratum; int precision; int leap; int xmtcnt; int filter_nextpt; int /*<<< orphan*/  offset; int /*<<< orphan*/  dispersion; scalar_t__ delay; int /*<<< orphan*/ * filter_offset; int /*<<< orphan*/ * filter_delay; int /*<<< orphan*/  xmt; int /*<<< orphan*/  org; int /*<<< orphan*/  reftime; int /*<<< orphan*/  rootdisp; scalar_t__ rootdelay; int /*<<< orphan*/  refid; int /*<<< orphan*/  trust; int /*<<< orphan*/  srcadr; } ;
typedef  int /*<<< orphan*/  s_fp ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int NTP_SHIFT ; 
 int PEER_SHIFT ; 
 scalar_t__ REFID_ISTEXT (int) ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 char* fptoa (int /*<<< orphan*/ ,int) ; 
 scalar_t__ isprint (char const) ; 
 char* lfptoa (int /*<<< orphan*/ *,int) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 char* numtoa (int /*<<< orphan*/ ) ; 
 char* prettydate (int /*<<< orphan*/ *) ; 
 char* stoa (int /*<<< orphan*/ *) ; 
 int sys_samples ; 
 char* ufptoa (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
print_server(
	register struct server *pp,
	FILE *fp
	)
{
	register int i;
	char junk[5];
	const char *str;

	if (pp->stratum == 0)		/* Nothing received => nothing to print */
		return;

	if (!debug) {
		(void) fprintf(fp, "server %s, stratum %d, offset %s, delay %s\n",
				   stoa(&pp->srcadr), pp->stratum,
				   lfptoa(&pp->offset, 6), fptoa((s_fp)pp->delay, 5));
		return;
	}

	(void) fprintf(fp, "server %s, port %d\n",
			   stoa(&pp->srcadr), ntohs(((struct sockaddr_in*)&(pp->srcadr))->sin_port));

	(void) fprintf(fp, "stratum %d, precision %d, leap %c%c, trust %03o\n",
			   pp->stratum, pp->precision,
			   pp->leap & 0x2 ? '1' : '0',
			   pp->leap & 0x1 ? '1' : '0',
			   pp->trust);

	if (REFID_ISTEXT(pp->stratum)) {
		str = (char *) &pp->refid;
		for (i=0; i<4 && str[i]; i++) {
			junk[i] = (isprint(str[i]) ? str[i] : '.');
		}
		junk[i] = 0; // force terminating 0
		str = junk;
	} else {
		str = numtoa(pp->refid);
	}
	(void) fprintf(fp,
			"refid [%s], root delay %s, root dispersion %s\n",
			str, fptoa((s_fp)pp->rootdelay, 6),
			ufptoa(pp->rootdisp, 6));

	if (pp->xmtcnt != pp->filter_nextpt)
		(void) fprintf(fp, "transmitted %d, in filter %d\n",
			   pp->xmtcnt, pp->filter_nextpt);

	(void) fprintf(fp, "reference time:      %s\n",
			   prettydate(&pp->reftime));
	(void) fprintf(fp, "originate timestamp: %s\n",
			   prettydate(&pp->org));
	(void) fprintf(fp, "transmit timestamp:  %s\n",
			   prettydate(&pp->xmt));

	if (sys_samples > 1) {
		(void) fprintf(fp, "filter delay: ");
		for (i = 0; i < NTP_SHIFT; i++) {
			if (i == (NTP_SHIFT>>1))
				(void) fprintf(fp, "\n              ");
			(void) fprintf(fp, " %-10.10s", 
				(i<sys_samples ? fptoa(pp->filter_delay[i], 5) : "----"));
		}
		(void) fprintf(fp, "\n");

		(void) fprintf(fp, "filter offset:");
		for (i = 0; i < PEER_SHIFT; i++) {
			if (i == (PEER_SHIFT>>1))
				(void) fprintf(fp, "\n              ");
			(void) fprintf(fp, " %-10.10s", 
				(i<sys_samples ? lfptoa(&pp->filter_offset[i], 6): "----"));
		}
		(void) fprintf(fp, "\n");
	}

	(void) fprintf(fp, "delay %s, dispersion %s, ",
			   fptoa((s_fp)pp->delay, 5), ufptoa(pp->dispersion, 5));

	(void) fprintf(fp, "offset %s\n\n",
			   lfptoa(&pp->offset, 6));
}