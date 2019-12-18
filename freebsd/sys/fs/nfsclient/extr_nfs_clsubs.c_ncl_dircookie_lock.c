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
struct nfsnode {int n_flag; int /*<<< orphan*/  n_mtx; } ;

/* Variables and functions */
 int NDIRCOOKIELK ; 
 int /*<<< orphan*/  NFSLOCKNODE (struct nfsnode*) ; 
 int /*<<< orphan*/  NFSUNLOCKNODE (struct nfsnode*) ; 
 int /*<<< orphan*/  PZERO ; 
 int /*<<< orphan*/  msleep (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void 
ncl_dircookie_lock(struct nfsnode *np)
{
	NFSLOCKNODE(np);
	while (np->n_flag & NDIRCOOKIELK)
		(void) msleep(&np->n_flag, &np->n_mtx, PZERO, "nfsdirlk", 0);
	np->n_flag |= NDIRCOOKIELK;
	NFSUNLOCKNODE(np);
}