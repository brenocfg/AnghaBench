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
typedef  int /*<<< orphan*/  mbstate_t ;

/* Variables and functions */
 int fnmatch1 (char const*,char const*,char const*,int,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 

int
fnmatch(const char *pattern, const char *string, int flags)
{
	static const mbstate_t initial;

	return (fnmatch1(pattern, string, string, flags, initial, initial));
}