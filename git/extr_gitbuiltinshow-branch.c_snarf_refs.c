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
 int /*<<< orphan*/  append_head_ref ; 
 int /*<<< orphan*/  append_remote_ref ; 
 int /*<<< orphan*/  for_each_ref (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ref_name_cnt ; 
 int /*<<< orphan*/  sort_ref_range (int,int) ; 

__attribute__((used)) static void snarf_refs(int head, int remotes)
{
	if (head) {
		int orig_cnt = ref_name_cnt;

		for_each_ref(append_head_ref, NULL);
		sort_ref_range(orig_cnt, ref_name_cnt);
	}
	if (remotes) {
		int orig_cnt = ref_name_cnt;

		for_each_ref(append_remote_ref, NULL);
		sort_ref_range(orig_cnt, ref_name_cnt);
	}
}