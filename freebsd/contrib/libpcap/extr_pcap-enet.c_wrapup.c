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
struct enstats {int enStat_Rcnt; scalar_t__ enStat_Rdrops; int enStat_Reads; int enStat_MaxRead; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIOSTATS ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,...) ; 
 int ioctl (int,int /*<<< orphan*/ ,struct enstats*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

void
wrapup(int fd)
{
#ifdef	IBMRTPC
	struct enstats es;

	if (ioctl(fd, EIOSTATS, &es) == -1) {
		perror("tcpdump: enet ioctl EIOSTATS error");
		exit(-1);
	}

	fprintf(stderr, "%d packets queued", es.enStat_Rcnt);
	if (es.enStat_Rdrops > 0)
		fprintf(stderr, ", %d dropped", es.enStat_Rdrops);
	if (es.enStat_Reads > 0)
		fprintf(stderr, ", %d tcpdump %s", es.enStat_Reads,
				es.enStat_Reads > 1 ? "reads" : "read");
	if (es.enStat_MaxRead > 1)
		fprintf(stderr, ", %d packets in largest read",
			es.enStat_MaxRead);
	putc('\n', stderr);
#endif	/* IBMRTPC */
	close(fd);
}