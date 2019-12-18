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
typedef  char uint8_t ;
typedef  int uint16_t ;
struct TYPE_2__ {int /*<<< orphan*/  cpuc_dtrace_flags; } ;

/* Variables and functions */
 int volatile CPU_DTRACE_FAULT ; 
 TYPE_1__* cpu_core ; 
 size_t curcpu ; 
 char dtrace_load8 (uintptr_t) ; 

__attribute__((used)) static int
dtrace_strncmp(char *s1, char *s2, size_t limit)
{
	uint8_t c1, c2;
	volatile uint16_t *flags;

	if (s1 == s2 || limit == 0)
		return (0);

	flags = (volatile uint16_t *)&cpu_core[curcpu].cpuc_dtrace_flags;

	do {
		if (s1 == NULL) {
			c1 = '\0';
		} else {
			c1 = dtrace_load8((uintptr_t)s1++);
		}

		if (s2 == NULL) {
			c2 = '\0';
		} else {
			c2 = dtrace_load8((uintptr_t)s2++);
		}

		if (c1 != c2)
			return (c1 - c2);
	} while (--limit && c1 != '\0' && !(*flags & CPU_DTRACE_FAULT));

	return (0);
}