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
struct stat {scalar_t__ st_dev; } ;

/* Variables and functions */
 scalar_t__ p_stat (char const*,struct stat*) ; 

__attribute__((used)) static bool can_link(const char *src, const char *dst, int link)
{
#ifdef GIT_WIN32
	GIT_UNUSED(src);
	GIT_UNUSED(dst);
	GIT_UNUSED(link);
	return false;
#else

	struct stat st_src, st_dst;

	if (!link)
		return false;

	if (p_stat(src, &st_src) < 0)
		return false;

	if (p_stat(dst, &st_dst) < 0)
		return false;

	return st_src.st_dev == st_dst.st_dev;
#endif
}