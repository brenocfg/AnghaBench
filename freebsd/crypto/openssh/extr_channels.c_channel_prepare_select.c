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
typedef  int u_int ;
typedef  int /*<<< orphan*/  time_t ;
struct ssh {TYPE_1__* chanctxt; } ;
typedef  int /*<<< orphan*/  fd_set ;
typedef  int /*<<< orphan*/  fd_mask ;
struct TYPE_2__ {int /*<<< orphan*/  channel_max_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHAN_PRE ; 
 int MAXIMUM (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFDBITS ; 
 int SIZE_MAX ; 
 int /*<<< orphan*/  channel_before_prepare_select (struct ssh*) ; 
 int /*<<< orphan*/  channel_handler (struct ssh*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fatal (char*,int) ; 
 int howmany (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ssh_packet_is_rekeying (struct ssh*) ; 
 int /*<<< orphan*/ * xreallocarray (int /*<<< orphan*/ *,int,int) ; 

void
channel_prepare_select(struct ssh *ssh, fd_set **readsetp, fd_set **writesetp,
    int *maxfdp, u_int *nallocp, time_t *minwait_secs)
{
	u_int n, sz, nfdset;

	channel_before_prepare_select(ssh); /* might update channel_max_fd */

	n = MAXIMUM(*maxfdp, ssh->chanctxt->channel_max_fd);

	nfdset = howmany(n+1, NFDBITS);
	/* Explicitly test here, because xrealloc isn't always called */
	if (nfdset && SIZE_MAX / nfdset < sizeof(fd_mask))
		fatal("channel_prepare_select: max_fd (%d) is too large", n);
	sz = nfdset * sizeof(fd_mask);

	/* perhaps check sz < nalloc/2 and shrink? */
	if (*readsetp == NULL || sz > *nallocp) {
		*readsetp = xreallocarray(*readsetp, nfdset, sizeof(fd_mask));
		*writesetp = xreallocarray(*writesetp, nfdset, sizeof(fd_mask));
		*nallocp = sz;
	}
	*maxfdp = n;
	memset(*readsetp, 0, sz);
	memset(*writesetp, 0, sz);

	if (!ssh_packet_is_rekeying(ssh))
		channel_handler(ssh, CHAN_PRE, *readsetp, *writesetp,
		    minwait_secs);
}