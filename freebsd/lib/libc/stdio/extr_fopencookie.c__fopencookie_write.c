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
struct TYPE_2__ {scalar_t__ (* write ) (int /*<<< orphan*/ ,char const*,size_t) ;} ;
struct fopencookie_thunk {int /*<<< orphan*/  foc_cookie; TYPE_1__ foc_io; } ;

/* Variables and functions */
 scalar_t__ stub1 (int /*<<< orphan*/ ,char const*,size_t) ; 

__attribute__((used)) static int
_fopencookie_write(void *cookie, const char *buf, int size)
{
	struct fopencookie_thunk *thunk;

	thunk = cookie;

	/* Writes to a stream with NULL write discard data. */
	if (thunk->foc_io.write == NULL)
		return (size);

	return ((int)thunk->foc_io.write(thunk->foc_cookie, buf,
		(size_t)size));
}