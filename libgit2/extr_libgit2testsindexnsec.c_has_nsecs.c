#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ nanoseconds; } ;
struct TYPE_5__ {scalar_t__ nanoseconds; } ;
struct TYPE_7__ {TYPE_2__ mtime; TYPE_1__ ctime; } ;
typedef  TYPE_3__ git_index_entry ;

/* Variables and functions */
 size_t git_index_entrycount (int /*<<< orphan*/ ) ; 
 TYPE_3__* git_index_get_byindex (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  repo_index ; 

__attribute__((used)) static bool has_nsecs(void)
{
	const git_index_entry *entry;
	size_t i;
	bool has_nsecs = false;

	for (i = 0; i < git_index_entrycount(repo_index); i++) {
		entry = git_index_get_byindex(repo_index, i);

		if (entry->ctime.nanoseconds || entry->mtime.nanoseconds) {
			has_nsecs = true;
			break;
		}
	}

	return has_nsecs;
}