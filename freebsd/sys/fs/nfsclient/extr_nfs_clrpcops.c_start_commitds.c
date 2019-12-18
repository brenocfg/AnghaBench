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
struct nfsclwritedsdorpc {int done; int /*<<< orphan*/  err; int /*<<< orphan*/  p; int /*<<< orphan*/  cred; int /*<<< orphan*/  minorvers; int /*<<< orphan*/  vers; int /*<<< orphan*/  fhp; int /*<<< orphan*/  dsp; int /*<<< orphan*/  len; int /*<<< orphan*/  off; int /*<<< orphan*/  vp; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFSCL_DEBUG (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsrpc_commitds (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
start_commitds(void *arg, int pending)
{
	struct nfsclwritedsdorpc *drpc;

	drpc = (struct nfsclwritedsdorpc *)arg;
	drpc->err = nfsrpc_commitds(drpc->vp, drpc->off, drpc->len,
	    drpc->dsp, drpc->fhp, drpc->vers, drpc->minorvers, drpc->cred,
	    drpc->p);
	drpc->done = 1;
	NFSCL_DEBUG(4, "start_commitds: err=%d\n", drpc->err);
}