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
typedef  int cc_t ;

/* Variables and functions */
 int _POSIX_VDISABLE ; 

__attribute__((used)) static cc_t
special_char_decode(u_int c)
{
#ifdef _POSIX_VDISABLE
	if (c == 255)
		return _POSIX_VDISABLE;
#endif /* _POSIX_VDISABLE */
	return c;
}