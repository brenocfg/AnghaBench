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
typedef  int u32 ;
struct TYPE_2__ {int* flags; } ;

/* Variables and functions */
 int NCAPINTS ; 
 TYPE_1__ cpu ; 
 int* err_flags ; 
 int* req_flags ; 

__attribute__((used)) static int check_cpuflags(void)
{
	u32 err;
	int i;

	err = 0;
	for (i = 0; i < NCAPINTS; i++) {
		err_flags[i] = req_flags[i] & ~cpu.flags[i];
		if (err_flags[i])
			err |= 1 << i;
	}

	return err;
}