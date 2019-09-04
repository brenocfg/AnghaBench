#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* replace_email; struct TYPE_4__* replace_name; struct TYPE_4__* real_email; struct TYPE_4__* real_name; } ;
typedef  TYPE_1__ git_mailmap_entry ;

/* Variables and functions */
 int /*<<< orphan*/  git__free (TYPE_1__*) ; 

__attribute__((used)) static void mailmap_entry_free(git_mailmap_entry *entry)
{
	if (!entry)
		return;

	git__free(entry->real_name);
	git__free(entry->real_email);
	git__free(entry->replace_name);
	git__free(entry->replace_email);
	git__free(entry);
}