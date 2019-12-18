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
struct combine_diff_path {char const* path; } ;

/* Variables and functions */

__attribute__((used)) static const char *path_path(void *obj)
{
	struct combine_diff_path *path = (struct combine_diff_path *)obj;

	return path->path;
}