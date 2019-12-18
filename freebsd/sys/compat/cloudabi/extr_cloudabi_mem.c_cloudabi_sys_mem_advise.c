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
struct thread {int dummy; } ;
struct cloudabi_sys_mem_advise_args {int advice; int /*<<< orphan*/  mapping_len; scalar_t__ mapping; } ;

/* Variables and functions */
#define  CLOUDABI_ADVICE_DONTNEED 132 
#define  CLOUDABI_ADVICE_NORMAL 131 
#define  CLOUDABI_ADVICE_RANDOM 130 
#define  CLOUDABI_ADVICE_SEQUENTIAL 129 
#define  CLOUDABI_ADVICE_WILLNEED 128 
 int EINVAL ; 
 int MADV_DONTNEED ; 
 int MADV_NORMAL ; 
 int MADV_RANDOM ; 
 int MADV_SEQUENTIAL ; 
 int MADV_WILLNEED ; 
 int kern_madvise (struct thread*,uintptr_t,int /*<<< orphan*/ ,int) ; 

int
cloudabi_sys_mem_advise(struct thread *td,
    struct cloudabi_sys_mem_advise_args *uap)
{
	int behav;

	switch (uap->advice) {
	case CLOUDABI_ADVICE_DONTNEED:
		behav = MADV_DONTNEED;
		break;
	case CLOUDABI_ADVICE_NORMAL:
		behav = MADV_NORMAL;
		break;
	case CLOUDABI_ADVICE_RANDOM:
		behav = MADV_RANDOM;
		break;
	case CLOUDABI_ADVICE_SEQUENTIAL:
		behav = MADV_SEQUENTIAL;
		break;
	case CLOUDABI_ADVICE_WILLNEED:
		behav = MADV_WILLNEED;
		break;
	default:
		return (EINVAL);
	}

	return (kern_madvise(td, (uintptr_t)uap->mapping, uap->mapping_len,
	    behav));
}