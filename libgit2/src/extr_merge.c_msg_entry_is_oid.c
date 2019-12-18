#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct merge_msg_entry {scalar_t__ written; TYPE_1__* merge_head; } ;
struct TYPE_2__ {int /*<<< orphan*/ * remote_url; int /*<<< orphan*/ * ref_name; } ;

/* Variables and functions */

__attribute__((used)) static int msg_entry_is_oid(
	const struct merge_msg_entry *merge_msg_entry)
{
	return (merge_msg_entry->written == 0 &&
		merge_msg_entry->merge_head->ref_name == NULL &&
		merge_msg_entry->merge_head->remote_url == NULL);
}