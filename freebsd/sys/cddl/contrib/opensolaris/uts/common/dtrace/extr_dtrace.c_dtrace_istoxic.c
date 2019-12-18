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
struct TYPE_4__ {uintptr_t cpuc_dtrace_illval; } ;
struct TYPE_3__ {uintptr_t dtt_base; uintptr_t dtt_limit; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_DTRACE_BADADDR ; 
 int /*<<< orphan*/  DTRACE_CPUFLAG_SET (int /*<<< orphan*/ ) ; 
 TYPE_2__* cpu_core ; 
 size_t curcpu ; 
 TYPE_1__* dtrace_toxrange ; 
 int dtrace_toxranges ; 

__attribute__((used)) static int
dtrace_istoxic(uintptr_t kaddr, size_t size)
{
	uintptr_t taddr, tsize;
	int i;

	for (i = 0; i < dtrace_toxranges; i++) {
		taddr = dtrace_toxrange[i].dtt_base;
		tsize = dtrace_toxrange[i].dtt_limit - taddr;

		if (kaddr - taddr < tsize) {
			DTRACE_CPUFLAG_SET(CPU_DTRACE_BADADDR);
			cpu_core[curcpu].cpuc_dtrace_illval = kaddr;
			return (1);
		}

		if (taddr - kaddr < size) {
			DTRACE_CPUFLAG_SET(CPU_DTRACE_BADADDR);
			cpu_core[curcpu].cpuc_dtrace_illval = taddr;
			return (1);
		}
	}

	return (0);
}