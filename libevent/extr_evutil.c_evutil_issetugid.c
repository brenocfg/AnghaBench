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
 scalar_t__ getegid () ; 
 scalar_t__ geteuid () ; 
 scalar_t__ getgid () ; 
 scalar_t__ getuid () ; 
 int issetugid () ; 

__attribute__((used)) static int
evutil_issetugid(void)
{
#ifdef EVENT__HAVE_ISSETUGID
	return issetugid();
#else

#ifdef EVENT__HAVE_GETEUID
	if (getuid() != geteuid())
		return 1;
#endif
#ifdef EVENT__HAVE_GETEGID
	if (getgid() != getegid())
		return 1;
#endif
	return 0;
#endif
}