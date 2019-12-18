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
struct TYPE_2__ {int (* close ) (int /*<<< orphan*/ ) ;} ;
struct fopencookie_thunk {int /*<<< orphan*/  foc_cookie; TYPE_1__ foc_io; } ;

/* Variables and functions */
 int errno ; 
 int /*<<< orphan*/  free (struct fopencookie_thunk*) ; 
 int stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
_fopencookie_close(void *cookie)
{
	struct fopencookie_thunk *thunk;
	int ret, serrno;

	ret = 0;
	thunk = cookie;
	if (thunk->foc_io.close != NULL)
		ret = thunk->foc_io.close(thunk->foc_cookie);

	serrno = errno;
	free(thunk);
	errno = serrno;
	return (ret);
}