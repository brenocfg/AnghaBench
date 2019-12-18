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
typedef  scalar_t__ uint32_t ;
struct vm {int dummy; } ;
struct vatpit {int dummy; } ;

/* Variables and functions */
 scalar_t__ TMR2_OUT_STS ; 
 int /*<<< orphan*/  VATPIT_LOCK (struct vatpit*) ; 
 int /*<<< orphan*/  VATPIT_UNLOCK (struct vatpit*) ; 
 scalar_t__ vatpit_get_out (struct vatpit*,int) ; 
 struct vatpit* vm_atpit (struct vm*) ; 

int
vatpit_nmisc_handler(struct vm *vm, int vcpuid, bool in, int port, int bytes,
    uint32_t *eax)
{
	struct vatpit *vatpit;

	vatpit = vm_atpit(vm);

	if (in) {
			VATPIT_LOCK(vatpit);
			if (vatpit_get_out(vatpit, 2))
				*eax = TMR2_OUT_STS;
			else
				*eax = 0;

			VATPIT_UNLOCK(vatpit);
	}

	return (0);
}