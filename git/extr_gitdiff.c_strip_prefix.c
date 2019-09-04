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
 int /*<<< orphan*/  is_absolute_path (char const*) ; 

__attribute__((used)) static void strip_prefix(int prefix_length, const char **namep, const char **otherp)
{
	/* Strip the prefix but do not molest /dev/null and absolute paths */
	if (*namep && !is_absolute_path(*namep)) {
		*namep += prefix_length;
		if (**namep == '/')
			++*namep;
	}
	if (*otherp && !is_absolute_path(*otherp)) {
		*otherp += prefix_length;
		if (**otherp == '/')
			++*otherp;
	}
}