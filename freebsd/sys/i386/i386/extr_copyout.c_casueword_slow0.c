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
typedef  scalar_t__ vm_offset_t ;
typedef  int /*<<< orphan*/  u_int ;
struct casueword_arg0 {int /*<<< orphan*/  newval; int /*<<< orphan*/  oldval; scalar_t__ res; } ;

/* Variables and functions */
 scalar_t__ atomic_fcmpset_int (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
casueword_slow0(vm_offset_t kva, void *arg)
{
	struct casueword_arg0 *ca;

	ca = arg;
	ca->res = 1 - atomic_fcmpset_int((u_int *)kva, &ca->oldval,
	    ca->newval);
}