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
 scalar_t__ ends_with (char const*,char*) ; 
 int /*<<< orphan*/  starts_with (char const*,char*) ; 

__attribute__((used)) static int pack_copy_priority(const char *name)
{
	if (!starts_with(name, "pack"))
		return 0;
	if (ends_with(name, ".keep"))
		return 1;
	if (ends_with(name, ".pack"))
		return 2;
	if (ends_with(name, ".idx"))
		return 3;
	return 4;
}