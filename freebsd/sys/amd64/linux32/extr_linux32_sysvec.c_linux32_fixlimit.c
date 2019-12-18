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
 void* linux32_maxdsiz ; 
 void* linux32_maxssiz ; 
 void* linux32_maxvmem ; 

__attribute__((used)) static void
linux32_fixlimit(struct rlimit *rl, int which)
{

	switch (which) {
	case RLIMIT_DATA:
		if (linux32_maxdsiz != 0) {
			if (rl->rlim_cur > linux32_maxdsiz)
				rl->rlim_cur = linux32_maxdsiz;
			if (rl->rlim_max > linux32_maxdsiz)
				rl->rlim_max = linux32_maxdsiz;
		}
		break;
	case RLIMIT_STACK:
		if (linux32_maxssiz != 0) {
			if (rl->rlim_cur > linux32_maxssiz)
				rl->rlim_cur = linux32_maxssiz;
			if (rl->rlim_max > linux32_maxssiz)
				rl->rlim_max = linux32_maxssiz;
		}
		break;
	case RLIMIT_VMEM:
		if (linux32_maxvmem != 0) {
			if (rl->rlim_cur > linux32_maxvmem)
				rl->rlim_cur = linux32_maxvmem;
			if (rl->rlim_max > linux32_maxvmem)
				rl->rlim_max = linux32_maxvmem;
		}
		break;
	}
}