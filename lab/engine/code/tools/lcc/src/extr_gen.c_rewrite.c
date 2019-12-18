#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ inst; } ;
struct TYPE_14__ {TYPE_1__ x; } ;
struct TYPE_13__ {int /*<<< orphan*/  (* _label ) (TYPE_3__*) ;} ;
struct TYPE_11__ {TYPE_2__ x; } ;
typedef  TYPE_3__* Node ;

/* Variables and functions */
 TYPE_10__* IR ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dumpcover (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dumptree (TYPE_3__*) ; 
 int /*<<< orphan*/  fprint (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  prelabel (TYPE_3__*) ; 
 int /*<<< orphan*/  reduce (TYPE_3__*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

__attribute__((used)) static void rewrite(Node p) {
	assert(p->x.inst == 0);
	prelabel(p);
	debug(dumptree(p));
	debug(fprint(stderr, "\n"));
	(*IR->x._label)(p);
	debug(dumpcover(p, 1, 0));
	reduce(p, 1);
}