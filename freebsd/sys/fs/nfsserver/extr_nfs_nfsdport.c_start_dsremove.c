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
struct nfsrvdsremove {int done; int /*<<< orphan*/  err; int /*<<< orphan*/  p; int /*<<< orphan*/  tcred; int /*<<< orphan*/  fname; int /*<<< orphan*/  dvp; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFSD_DEBUG (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsrv_dsremove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
start_dsremove(void *arg, int pending)
{
	struct nfsrvdsremove *dsrm;

	dsrm = (struct nfsrvdsremove *)arg;
	dsrm->err = nfsrv_dsremove(dsrm->dvp, dsrm->fname, dsrm->tcred,
	    dsrm->p);
	dsrm->done = 1;
	NFSD_DEBUG(4, "start_dsremove: err=%d\n", dsrm->err);
}