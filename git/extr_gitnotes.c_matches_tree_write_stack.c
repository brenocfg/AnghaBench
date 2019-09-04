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
struct tree_write_stack {char const* path; } ;

/* Variables and functions */

__attribute__((used)) static inline int matches_tree_write_stack(struct tree_write_stack *tws,
		const char *full_path)
{
	return  full_path[0] == tws->path[0] &&
		full_path[1] == tws->path[1] &&
		full_path[2] == '/';
}