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
struct finfo {int flag; scalar_t__ forward_fd; int /*<<< orphan*/  uaddr; int /*<<< orphan*/  caller_addr; } ;

/* Variables and functions */
 struct finfo* FINFO ; 
 int FINFO_ACTIVE ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netbuffree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpcb_rmtcalls ; 
 scalar_t__ svc_maxfd ; 

__attribute__((used)) static int
free_slot_by_index(int index)
{
	struct finfo	*fi;

	fi = &FINFO[index];
	if (fi->flag & FINFO_ACTIVE) {
		netbuffree(fi->caller_addr);
		/* XXX may be too big, but can't access xprt array here */
		if (fi->forward_fd >= svc_maxfd)
			svc_maxfd--;
		free(fi->uaddr);
		fi->flag &= ~FINFO_ACTIVE;
		rpcb_rmtcalls--;
		return (1);
	}
	return (0);
}