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
 int /*<<< orphan*/  endgrent () ; 
 int /*<<< orphan*/  fix_yp_bugs () ; 

void
tw_grpname_end(void)
{
#ifdef YPBUGS
    fix_yp_bugs();
#endif
#if !defined(_VMS_POSIX) && !defined(_OSD_POSIX) && !defined(WINNT_NATIVE) && !defined (__ANDROID__)
   (void) endgrent();
#endif /* !_VMS_POSIX && !_OSD_POSIX && !WINNT_NATIVE */
}