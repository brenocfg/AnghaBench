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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_2__ {uintptr_t cpuc_dtrace_illval; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_DTRACE_BADADDR ; 
 int /*<<< orphan*/  DTRACE_CPUFLAG_SET (int /*<<< orphan*/ ) ; 
 scalar_t__ copyout (void const*,void*,size_t) ; 
 TYPE_1__* cpu_core ; 
 size_t curcpu ; 
 scalar_t__ dtrace_copycheck (uintptr_t,uintptr_t,size_t) ; 
 size_t strlen (char const*) ; 

void
dtrace_copyoutstr(uintptr_t kaddr, uintptr_t uaddr, size_t size,
    volatile uint16_t *flags)
{
	size_t len;

	if (dtrace_copycheck(uaddr, kaddr, size)) {
		len = strlen((const char *)kaddr);
		if (len > size)
			len = size;

		if (copyout((const void *)kaddr, (void *)uaddr, len)) {
			DTRACE_CPUFLAG_SET(CPU_DTRACE_BADADDR);
			cpu_core[curcpu].cpuc_dtrace_illval = (uintptr_t)uaddr;
		}
	}
}