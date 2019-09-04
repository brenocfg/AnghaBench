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
 char const* prefix_path (char const*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static const char *add_prefix(const char *prefix, const char *path)
{
	return prefix_path(prefix, prefix ? strlen(prefix) : 0, path);
}