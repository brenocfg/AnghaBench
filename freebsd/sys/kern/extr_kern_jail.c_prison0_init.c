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
struct TYPE_4__ {int /*<<< orphan*/  pr_osrelease; int /*<<< orphan*/  pr_osreldate; int /*<<< orphan*/  pr_cpuset; } ;
struct TYPE_3__ {int /*<<< orphan*/  td_cpuset; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpuset_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osreldate ; 
 int /*<<< orphan*/  osrelease ; 
 TYPE_2__ prison0 ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_1__ thread0 ; 

void
prison0_init(void)
{

	prison0.pr_cpuset = cpuset_ref(thread0.td_cpuset);
	prison0.pr_osreldate = osreldate;
	strlcpy(prison0.pr_osrelease, osrelease, sizeof(prison0.pr_osrelease));
}