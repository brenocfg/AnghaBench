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
struct cloudabi_sys_file_advise_args {int advice; int /*<<< orphan*/  len; int /*<<< orphan*/  offset; int /*<<< orphan*/  fd; } ;

/* Variables and functions */
#define  CLOUDABI_ADVICE_DONTNEED 133 
#define  CLOUDABI_ADVICE_NOREUSE 132 
#define  CLOUDABI_ADVICE_NORMAL 131 
#define  CLOUDABI_ADVICE_RANDOM 130 
#define  CLOUDABI_ADVICE_SEQUENTIAL 129 
#define  CLOUDABI_ADVICE_WILLNEED 128 
 int EINVAL ; 
 int POSIX_FADV_DONTNEED ; 
 int POSIX_FADV_NOREUSE ; 
 int POSIX_FADV_NORMAL ; 
 int POSIX_FADV_RANDOM ; 
 int POSIX_FADV_SEQUENTIAL ; 
 int POSIX_FADV_WILLNEED ; 
 int kern_posix_fadvise (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
cloudabi_sys_file_advise(struct thread *td,
    struct cloudabi_sys_file_advise_args *uap)
{
	int advice;

	switch (uap->advice) {
	case CLOUDABI_ADVICE_DONTNEED:
		advice = POSIX_FADV_DONTNEED;
		break;
	case CLOUDABI_ADVICE_NOREUSE:
		advice = POSIX_FADV_NOREUSE;
		break;
	case CLOUDABI_ADVICE_NORMAL:
		advice = POSIX_FADV_NORMAL;
		break;
	case CLOUDABI_ADVICE_RANDOM:
		advice = POSIX_FADV_RANDOM;
		break;
	case CLOUDABI_ADVICE_SEQUENTIAL:
		advice = POSIX_FADV_SEQUENTIAL;
		break;
	case CLOUDABI_ADVICE_WILLNEED:
		advice = POSIX_FADV_WILLNEED;
		break;
	default:
		return (EINVAL);
	}

	return (kern_posix_fadvise(td, uap->fd, uap->offset, uap->len, advice));
}