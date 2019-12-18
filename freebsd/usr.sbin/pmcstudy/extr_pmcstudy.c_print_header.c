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
 int MAX_CPU ; 
 int cpu_count_out ; 
 scalar_t__* glob_cpu ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
print_header(void)
{
	int i, cnt, printed_cnt;

	printf("*********************************\n");
	for(i=0, cnt=0; i<MAX_CPU; i++) {
		if (glob_cpu[i]) {
			cnt++;
		}
	}	
	cpu_count_out = cnt;
	for(i=0, printed_cnt=0; i<MAX_CPU; i++) {
		if (glob_cpu[i]) {
			printf("CPU%d", i);
			printed_cnt++;
		}
		if (printed_cnt == cnt) {
			printf("\n");
			break;
		} else {
			printf("\t");
		}
	}
}