#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_offset_t ;
struct env_var {char* ev_name; char* ev_value; struct env_var* ev_next; } ;
struct TYPE_2__ {int (* arch_copyin ) (char*,scalar_t__,size_t) ;} ;

/* Variables and functions */
 TYPE_1__ archsw ; 
 struct env_var* environ ; 
 size_t strlen (char*) ; 
 int stub1 (char*,scalar_t__,size_t) ; 
 int stub2 (char*,scalar_t__,int) ; 
 int stub3 (char*,scalar_t__,size_t) ; 
 int stub4 (char*,scalar_t__,int) ; 
 int stub5 (char*,scalar_t__,int) ; 

__attribute__((used)) static vm_offset_t
bi_copyenv(vm_offset_t start)
{
	struct env_var *ep;
	vm_offset_t addr, last;
	size_t len;

	addr = last = start;

	/* Traverse the environment. */
	for (ep = environ; ep != NULL; ep = ep->ev_next) {
		len = strlen(ep->ev_name);
		if ((size_t)archsw.arch_copyin(ep->ev_name, addr, len) != len)
			break;
		addr += len;
		if (archsw.arch_copyin("=", addr, 1) != 1)
			break;
		addr++;
		if (ep->ev_value != NULL) {
			len = strlen(ep->ev_value);
			if ((size_t)archsw.arch_copyin(ep->ev_value, addr, len) != len)
				break;
			addr += len;
		}
		if (archsw.arch_copyin("", addr, 1) != 1)
			break;
		last = ++addr;
	}

	if (archsw.arch_copyin("", last++, 1) != 1)
		last = start;
	return(last);
}