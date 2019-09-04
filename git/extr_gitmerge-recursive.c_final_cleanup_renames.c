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
struct rename_info {int /*<<< orphan*/  merge_renames; int /*<<< orphan*/  head_renames; } ;

/* Variables and functions */
 int /*<<< orphan*/  final_cleanup_rename (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void final_cleanup_renames(struct rename_info *re_info)
{
	final_cleanup_rename(re_info->head_renames);
	final_cleanup_rename(re_info->merge_renames);
}