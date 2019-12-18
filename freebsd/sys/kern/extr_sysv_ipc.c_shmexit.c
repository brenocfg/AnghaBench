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
struct vmspace {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  shmexit_hook (struct vmspace*) ; 

void
shmexit(struct vmspace *vm)
{

	if (shmexit_hook != NULL)
		shmexit_hook(vm);
	return;
}