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
typedef  int uint64_t ;
typedef  int u_int ;

/* Variables and functions */
 int VM_INTINFO_DEL_ERRCODE ; 
#define  VM_INTINFO_HWINTR 130 
#define  VM_INTINFO_NMI 129 
#define  VM_INTINFO_SWINTR 128 
 int VM_INTINFO_TYPE ; 
 int VM_INTINFO_VALID ; 
 scalar_t__ VM_INTINFO_VECTOR (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
print_intinfo(const char *banner, uint64_t info)
{
	int type;

	printf("%s:\t", banner);
	if (info & VM_INTINFO_VALID) {
		type = info & VM_INTINFO_TYPE;
		switch (type) {
		case VM_INTINFO_HWINTR:
			printf("extint");
			break;
		case VM_INTINFO_NMI:
			printf("nmi");
			break;
		case VM_INTINFO_SWINTR:
			printf("swint");
			break;
		default:
			printf("exception");
			break;
		}
		printf(" vector %d", (int)VM_INTINFO_VECTOR(info));
		if (info & VM_INTINFO_DEL_ERRCODE)
			printf(" errcode %#x", (u_int)(info >> 32));
	} else {
		printf("n/a");
	}
	printf("\n");
}