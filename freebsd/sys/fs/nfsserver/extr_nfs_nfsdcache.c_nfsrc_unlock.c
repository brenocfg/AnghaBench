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
struct nfsrvcache {int /*<<< orphan*/  rc_flag; } ;
struct mtx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RC_LOCKED ; 
 int /*<<< orphan*/  mtx_lock (struct mtx*) ; 
 int /*<<< orphan*/  mtx_unlock (struct mtx*) ; 
 struct mtx* nfsrc_cachemutex (struct nfsrvcache*) ; 
 int /*<<< orphan*/  nfsrc_wanted (struct nfsrvcache*) ; 

__attribute__((used)) static void
nfsrc_unlock(struct nfsrvcache *rp)
{
	struct mtx *mutex;

	mutex = nfsrc_cachemutex(rp);
	mtx_lock(mutex);
	rp->rc_flag &= ~RC_LOCKED;
	nfsrc_wanted(rp);
	mtx_unlock(mutex);
}