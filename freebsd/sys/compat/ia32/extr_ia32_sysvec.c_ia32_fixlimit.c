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
struct rlimit {void* rlim_cur; void* rlim_max; } ;

/* Variables and functions */
#define  RLIMIT_DATA 130 
#define  RLIMIT_STACK 129 
#define  RLIMIT_VMEM 128 
 void* ia32_maxdsiz ; 
 void* ia32_maxssiz ; 
 void* ia32_maxvmem ; 

void
ia32_fixlimit(struct rlimit *rl, int which)
{

	switch (which) {
	case RLIMIT_DATA:
		if (ia32_maxdsiz != 0) {
			if (rl->rlim_cur > ia32_maxdsiz)
				rl->rlim_cur = ia32_maxdsiz;
			if (rl->rlim_max > ia32_maxdsiz)
				rl->rlim_max = ia32_maxdsiz;
		}
		break;
	case RLIMIT_STACK:
		if (ia32_maxssiz != 0) {
			if (rl->rlim_cur > ia32_maxssiz)
				rl->rlim_cur = ia32_maxssiz;
			if (rl->rlim_max > ia32_maxssiz)
				rl->rlim_max = ia32_maxssiz;
		}
		break;
	case RLIMIT_VMEM:
		if (ia32_maxvmem != 0) {
			if (rl->rlim_cur > ia32_maxvmem)
				rl->rlim_cur = ia32_maxvmem;
			if (rl->rlim_max > ia32_maxvmem)
				rl->rlim_max = ia32_maxvmem;
		}
		break;
	}
}