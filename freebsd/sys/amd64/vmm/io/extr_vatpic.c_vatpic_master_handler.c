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
typedef  int /*<<< orphan*/  uint32_t ;
struct vm {int dummy; } ;
struct vatpic {struct atpic* atpic; } ;
struct atpic {int dummy; } ;

/* Variables and functions */
 int vatpic_read (struct vatpic*,struct atpic*,int,int,int,int /*<<< orphan*/ *) ; 
 int vatpic_write (struct vatpic*,struct atpic*,int,int,int,int /*<<< orphan*/ *) ; 
 struct vatpic* vm_atpic (struct vm*) ; 

int
vatpic_master_handler(struct vm *vm, int vcpuid, bool in, int port, int bytes,
    uint32_t *eax)
{
	struct vatpic *vatpic;
	struct atpic *atpic;

	vatpic = vm_atpic(vm);
	atpic = &vatpic->atpic[0];

	if (bytes != 1)
		return (-1);
 
	if (in) {
		return (vatpic_read(vatpic, atpic, in, port, bytes, eax));
	}
 
	return (vatpic_write(vatpic, atpic, in, port, bytes, eax));
}