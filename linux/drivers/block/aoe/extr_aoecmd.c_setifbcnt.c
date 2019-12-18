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
struct net_device {int dummy; } ;
struct aoetgt {int minbcnt; struct aoeif* ifs; struct aoedev* d; } ;
struct aoeif {int bcnt; struct net_device* nd; } ;
struct aoedev {int dummy; } ;

/* Variables and functions */
 int NAOEIFS ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  setdbcnt (struct aoedev*) ; 

__attribute__((used)) static void
setifbcnt(struct aoetgt *t, struct net_device *nd, int bcnt)
{
	struct aoedev *d;
	struct aoeif *p, *e;
	int minbcnt;

	d = t->d;
	minbcnt = bcnt;
	p = t->ifs;
	e = p + NAOEIFS;
	for (; p < e; p++) {
		if (p->nd == NULL)
			break;		/* end of the valid interfaces */
		if (p->nd == nd) {
			p->bcnt = bcnt;	/* we're updating */
			nd = NULL;
		} else if (minbcnt > p->bcnt)
			minbcnt = p->bcnt; /* find the min interface */
	}
	if (nd) {
		if (p == e) {
			pr_err("aoe: device setifbcnt failure; too many interfaces.\n");
			return;
		}
		dev_hold(nd);
		p->nd = nd;
		p->bcnt = bcnt;
	}
	t->minbcnt = minbcnt;
	setdbcnt(d);
}