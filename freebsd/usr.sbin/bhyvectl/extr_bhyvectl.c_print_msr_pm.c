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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 char* msr_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*,int,char,char) ; 

__attribute__((used)) static inline void
print_msr_pm(uint64_t msr, int vcpu, int readable, int writeable)
{

	if (readable || writeable) {
		printf("%-20s[%d]\t\t%c%c\n", msr_name(msr), vcpu,
			readable ? 'R' : '-', writeable ? 'W' : '-');
	}
}