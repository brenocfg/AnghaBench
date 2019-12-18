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
struct TYPE_3__ {int /*<<< orphan*/ * _isinstruction; int /*<<< orphan*/ * _templates; int /*<<< orphan*/ * _string; } ;
struct TYPE_4__ {TYPE_1__ x; } ;

/* Variables and functions */
 TYPE_2__* IR ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fprint (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void dumprule(int rulenum) {
	assert(rulenum);
	fprint(stderr, "%s / %s", IR->x._string[rulenum],
		IR->x._templates[rulenum]);
	if (!IR->x._isinstruction[rulenum])
		fprint(stderr, "\n");
}