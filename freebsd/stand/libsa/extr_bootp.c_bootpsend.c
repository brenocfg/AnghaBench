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
typedef  int /*<<< orphan*/  u_short ;
struct iodesc {int dummy; } ;
struct bootp {int /*<<< orphan*/  bp_secs; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 scalar_t__ bot ; 
 scalar_t__ debug ; 
 scalar_t__ getsecs () ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sendudp (struct iodesc*,void*,size_t) ; 

__attribute__((used)) static ssize_t
bootpsend(struct iodesc *d, void *pkt, size_t len)
{
	struct bootp *bp;

#ifdef BOOTP_DEBUG
	if (debug)
		printf("bootpsend: d=%lx called.\n", (long)d);
#endif

	bp = pkt;
	bp->bp_secs = htons((u_short)(getsecs() - bot));

#ifdef BOOTP_DEBUG
	if (debug)
		printf("bootpsend: calling sendudp\n");
#endif

	return (sendudp(d, pkt, len));
}