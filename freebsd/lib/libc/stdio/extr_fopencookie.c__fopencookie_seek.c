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
struct TYPE_2__ {int (* seek ) (int /*<<< orphan*/ ,scalar_t__*,int) ;} ;
struct fopencookie_thunk {int /*<<< orphan*/  foc_cookie; TYPE_1__ foc_io; } ;
typedef  scalar_t__ off64_t ;
typedef  int fpos_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOTSUP ; 
#define  SEEK_CUR 130 
#define  SEEK_END 129 
#define  SEEK_SET 128 
 int /*<<< orphan*/  errno ; 
 int stub1 (int /*<<< orphan*/ ,scalar_t__*,int) ; 

__attribute__((used)) static fpos_t
_fopencookie_seek(void *cookie, fpos_t offset, int whence)
{
	struct fopencookie_thunk *thunk;
	off64_t off64;
	int res;

	switch (whence) {
	case SEEK_SET:
	case SEEK_CUR:
	case SEEK_END:
		break;
	default:
		/* fopencookie(3) only allows these three seek modes. */
		errno = EINVAL;
		return (-1);
	}

	thunk = cookie;

	/*
	 * If seek is NULL, it is not possible to perform seek operations on
	 * the stream.
	 */
	if (thunk->foc_io.seek == NULL) {
		errno = ENOTSUP;
		return (-1);
	}

	off64 = (off64_t)offset;
	res = thunk->foc_io.seek(thunk->foc_cookie, &off64, whence);
	if (res < 0)
		return (res);

	return ((fpos_t)off64);
}