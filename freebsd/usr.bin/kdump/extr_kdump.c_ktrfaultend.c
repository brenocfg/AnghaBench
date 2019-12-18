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
struct ktr_faultend {int result; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 
 char* sysdecode_vmresult (int) ; 

void
ktrfaultend(struct ktr_faultend *ktr)
{
	const char *str;

	str = sysdecode_vmresult(ktr->result);
	if (str != NULL)
		printf("%s", str);
	else
		printf("<invalid=%d>", ktr->result);
	printf("\n");
}