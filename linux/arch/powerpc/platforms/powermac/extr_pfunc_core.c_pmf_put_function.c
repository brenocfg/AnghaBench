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
struct pmf_function {TYPE_2__* dev; } ;
struct TYPE_4__ {TYPE_1__* handlers; } ;
struct TYPE_3__ {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  __pmf_put_function (struct pmf_function*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 

void pmf_put_function(struct pmf_function *func)
{
	if (func == NULL)
		return;
	module_put(func->dev->handlers->owner);
	__pmf_put_function(func);
}