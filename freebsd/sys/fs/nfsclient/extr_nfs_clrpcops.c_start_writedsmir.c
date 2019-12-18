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
struct nfsclwritedsdorpc {int done; int /*<<< orphan*/  err; int /*<<< orphan*/  p; int /*<<< orphan*/  cred; int /*<<< orphan*/  minorvers; int /*<<< orphan*/  vers; int /*<<< orphan*/  m; int /*<<< orphan*/  fhp; int /*<<< orphan*/  len; int /*<<< orphan*/  off; int /*<<< orphan*/  dsp; int /*<<< orphan*/  stateidp; int /*<<< orphan*/  must_commit; int /*<<< orphan*/  iomode; int /*<<< orphan*/  vp; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFSCL_DEBUG (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsrpc_writedsmir (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
start_writedsmir(void *arg, int pending)
{
	struct nfsclwritedsdorpc *drpc;

	drpc = (struct nfsclwritedsdorpc *)arg;
	drpc->err = nfsrpc_writedsmir(drpc->vp, &drpc->iomode,
	    &drpc->must_commit, drpc->stateidp, drpc->dsp, drpc->off, drpc->len,
	    drpc->fhp, drpc->m, drpc->vers, drpc->minorvers, drpc->cred,
	    drpc->p);
	drpc->done = 1;
	NFSCL_DEBUG(4, "start_writedsmir: err=%d\n", drpc->err);
}