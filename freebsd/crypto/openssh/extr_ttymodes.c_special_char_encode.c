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
typedef  int u_int ;
typedef  scalar_t__ cc_t ;

/* Variables and functions */
 scalar_t__ _POSIX_VDISABLE ; 

__attribute__((used)) static u_int
special_char_encode(cc_t c)
{
#ifdef _POSIX_VDISABLE
	if (c == _POSIX_VDISABLE)
		return 255;
#endif /* _POSIX_VDISABLE */
	return c;
}