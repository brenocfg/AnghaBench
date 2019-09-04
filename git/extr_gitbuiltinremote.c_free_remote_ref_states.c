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
struct ref_states {int /*<<< orphan*/  push; int /*<<< orphan*/  heads; int /*<<< orphan*/  tracked; int /*<<< orphan*/  stale; int /*<<< orphan*/  new_refs; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_push_info ; 
 int /*<<< orphan*/  string_list_clear (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  string_list_clear_func (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_remote_ref_states(struct ref_states *states)
{
	string_list_clear(&states->new_refs, 0);
	string_list_clear(&states->stale, 1);
	string_list_clear(&states->tracked, 0);
	string_list_clear(&states->heads, 0);
	string_list_clear_func(&states->push, clear_push_info);
}