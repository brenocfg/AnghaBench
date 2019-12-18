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
struct nfsnode {int /*<<< orphan*/  n_flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  NDIRCOOKIELK ; 
 int /*<<< orphan*/  NFSLOCKNODE (struct nfsnode*) ; 
 int /*<<< orphan*/  NFSUNLOCKNODE (struct nfsnode*) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 

void 
ncl_dircookie_unlock(struct nfsnode *np)
{
	NFSLOCKNODE(np);
	np->n_flag &= ~NDIRCOOKIELK;
	wakeup(&np->n_flag);
	NFSUNLOCKNODE(np);
}