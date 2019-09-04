#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {short** _nts; int /*<<< orphan*/  (* _kids ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ;} ;
struct TYPE_4__ {TYPE_1__ x; } ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 TYPE_2__* IR ; 
 int /*<<< orphan*/  dumprule (int) ; 
 int /*<<< orphan*/  fprint (int /*<<< orphan*/ ,char*,...) ; 
 int getrule (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reuse (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dumpcover(Node p, int nt, int in) {
	int rulenum, i;
	short *nts;
	Node kids[10];

	p = reuse(p, nt);
	rulenum = getrule(p, nt);
	nts = IR->x._nts[rulenum];
	fprint(stderr, "dumpcover(%x) = ", p);
	for (i = 0; i < in; i++)
		fprint(stderr, " ");
	dumprule(rulenum);
	(*IR->x._kids)(p, rulenum, kids);
	for (i = 0; nts[i]; i++)
		dumpcover(kids[i], nts[i], in+1);
}