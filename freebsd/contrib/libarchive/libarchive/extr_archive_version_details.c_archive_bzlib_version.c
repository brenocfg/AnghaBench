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
 char const* BZ2_bzlibVersion () ; 

const char *
archive_bzlib_version(void)
{
#ifdef HAVE_BZLIB_H
	return BZ2_bzlibVersion();
#else
	return NULL;
#endif
}