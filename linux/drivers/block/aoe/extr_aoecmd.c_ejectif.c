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
typedef  int ulong ;
struct net_device {int dummy; } ;
struct aoetgt {struct aoeif* ifs; } ;
struct aoeif {struct net_device* nd; } ;

/* Variables and functions */
 int NAOEIFS ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  memmove (struct aoeif*,struct aoeif*,int) ; 

__attribute__((used)) static void
ejectif(struct aoetgt *t, struct aoeif *ifp)
{
	struct aoeif *e;
	struct net_device *nd;
	ulong n;

	nd = ifp->nd;
	e = t->ifs + NAOEIFS - 1;
	n = (e - ifp) * sizeof *ifp;
	memmove(ifp, ifp+1, n);
	e->nd = NULL;
	dev_put(nd);
}