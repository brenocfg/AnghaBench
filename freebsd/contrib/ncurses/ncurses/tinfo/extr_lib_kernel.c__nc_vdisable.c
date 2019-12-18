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

/* Variables and functions */
 int VDISABLE ; 
 int /*<<< orphan*/  _PC_VDISABLE ; 
 int _POSIX_VDISABLE ; 
 scalar_t__ fpathconf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
_nc_vdisable(void)
{
    int value = -1;
#if defined(_POSIX_VDISABLE) && HAVE_UNISTD_H
    value = _POSIX_VDISABLE;
#endif
#if defined(_PC_VDISABLE)
    if (value == -1) {
	value = (int) fpathconf(0, _PC_VDISABLE);
	if (value == -1) {
	    value = 0377;
	}
    }
#elif defined(VDISABLE)
    if (value == -1)
	value = VDISABLE;
#endif
    return value;
}