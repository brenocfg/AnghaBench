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
struct traverse_info {int pathlen; } ;
struct name_entry {int dummy; } ;

/* Variables and functions */
 int tree_entry_len (struct name_entry const*) ; 

__attribute__((used)) static inline int traverse_path_len(const struct traverse_info *info, const struct name_entry *n)
{
	return info->pathlen + tree_entry_len(n);
}