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
struct common_dir {scalar_t__ path; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_to_trie (int /*<<< orphan*/ *,scalar_t__,struct common_dir*) ; 
 struct common_dir* common_list ; 
 int /*<<< orphan*/  common_trie ; 
 int common_trie_done_setup ; 

__attribute__((used)) static void init_common_trie(void)
{
	struct common_dir *p;

	if (common_trie_done_setup)
		return;

	for (p = common_list; p->path; p++)
		add_to_trie(&common_trie, p->path, p);

	common_trie_done_setup = 1;
}