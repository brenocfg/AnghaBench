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

/* Variables and functions */
 int SIGBUS ; 
 int SIGSEGV ; 
#define  T_DOUBLEFLT 131 
#define  T_PAGEFLT 130 
#define  T_PROTFLT 129 
#define  T_TSSFLT 128 

__attribute__((used)) static int
linux_translate_traps(int signal, int trap_code)
{

	if (signal != SIGBUS)
		return (signal);
	switch (trap_code) {
	case T_PROTFLT:
	case T_TSSFLT:
	case T_DOUBLEFLT:
	case T_PAGEFLT:
		return (SIGSEGV);
	default:
		return (signal);
	}
}