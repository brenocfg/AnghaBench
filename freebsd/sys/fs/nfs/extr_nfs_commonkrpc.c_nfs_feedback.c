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
typedef  scalar_t__ time_t ;
struct nfsmount {scalar_t__ nm_tprintf_delay; } ;
struct nfs_feedback_arg {int /*<<< orphan*/  nf_tprintfmsg; int /*<<< orphan*/  nf_td; struct nfsmount* nf_mount; scalar_t__ nf_lastmsg; } ;

/* Variables and functions */
#define  FEEDBACK_OK 130 
#define  FEEDBACK_RECONNECT 129 
#define  FEEDBACK_REXMIT2 128 
 scalar_t__ NFSD_MONOSEC ; 
 int /*<<< orphan*/  NFSSTA_TIMEO ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  nfs_down (struct nfsmount*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_up (struct nfsmount*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nfs_feedback(int type, int proc, void *arg)
{
	struct nfs_feedback_arg *nf = (struct nfs_feedback_arg *) arg;
	struct nfsmount *nmp = nf->nf_mount;
	time_t now;

	switch (type) {
	case FEEDBACK_REXMIT2:
	case FEEDBACK_RECONNECT:
		now = NFSD_MONOSEC;
		if (nf->nf_lastmsg + nmp->nm_tprintf_delay < now) {
			nfs_down(nmp, nf->nf_td,
			    "not responding", 0, NFSSTA_TIMEO);
			nf->nf_tprintfmsg = TRUE;
			nf->nf_lastmsg = now;
		}
		break;

	case FEEDBACK_OK:
		nfs_up(nf->nf_mount, nf->nf_td,
		    "is alive again", NFSSTA_TIMEO, nf->nf_tprintfmsg);
		break;
	}
}