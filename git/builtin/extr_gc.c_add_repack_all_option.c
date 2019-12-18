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
struct string_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  argv_array_push (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  argv_array_pushf (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  for_each_string_list (struct string_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  keep_one_pack ; 
 scalar_t__ prune_expire ; 
 int /*<<< orphan*/  repack ; 
 int /*<<< orphan*/  strcmp (scalar_t__,char*) ; 

__attribute__((used)) static void add_repack_all_option(struct string_list *keep_pack)
{
	if (prune_expire && !strcmp(prune_expire, "now"))
		argv_array_push(&repack, "-a");
	else {
		argv_array_push(&repack, "-A");
		if (prune_expire)
			argv_array_pushf(&repack, "--unpack-unreachable=%s", prune_expire);
	}

	if (keep_pack)
		for_each_string_list(keep_pack, keep_one_pack, NULL);
}