#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  suspend_state_t ;
struct TYPE_3__ {int /*<<< orphan*/  done; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int rtas_suspend_last_cpu (TYPE_1__*) ; 
 TYPE_1__ suspend_data ; 
 int /*<<< orphan*/  suspending ; 

__attribute__((used)) static int pseries_suspend_enter(suspend_state_t state)
{
	int rc = rtas_suspend_last_cpu(&suspend_data);

	atomic_set(&suspending, 0);
	atomic_set(&suspend_data.done, 1);
	return rc;
}