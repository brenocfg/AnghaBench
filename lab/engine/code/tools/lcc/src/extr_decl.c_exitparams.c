#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  defined; } ;
typedef  TYPE_1__* Symbol ;

/* Variables and functions */
 scalar_t__ PARAM ; 
 int /*<<< orphan*/  assert (TYPE_1__**) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  exitscope () ; 
 scalar_t__ level ; 

__attribute__((used)) static void exitparams(Symbol params[]) {
	assert(params);
	if (params[0] && !params[0]->defined)
		error("extraneous old-style parameter list\n");
	if (level > PARAM)
		exitscope();
	exitscope();
}