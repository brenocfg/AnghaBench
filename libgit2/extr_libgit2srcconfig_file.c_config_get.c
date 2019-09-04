#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * payload; int /*<<< orphan*/  free; } ;
typedef  TYPE_2__ git_config_entry ;
typedef  int /*<<< orphan*/  git_config_entries ;
typedef  int /*<<< orphan*/  git_config_backend ;
struct TYPE_7__ {int /*<<< orphan*/  readonly; } ;
struct TYPE_9__ {TYPE_1__ parent; } ;
typedef  TYPE_3__ diskfile_header ;

/* Variables and functions */
 int config_refresh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * diskfile_entries_take (TYPE_3__*) ; 
 int /*<<< orphan*/  free_diskfile_entry ; 
 int /*<<< orphan*/  git_config_entries_free (int /*<<< orphan*/ *) ; 
 int git_config_entries_get (TYPE_2__**,int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int config_get(git_config_backend *cfg, const char *key, git_config_entry **out)
{
	diskfile_header *h = (diskfile_header *)cfg;
	git_config_entries *entries = NULL;
	git_config_entry *entry;
	int error = 0;

	if (!h->parent.readonly && ((error = config_refresh(cfg)) < 0))
		return error;

	if ((entries = diskfile_entries_take(h)) == NULL)
		return -1;

	if ((error = (git_config_entries_get(&entry, entries, key))) < 0) {
		git_config_entries_free(entries);
		return error;
	}

	entry->free = free_diskfile_entry;
	entry->payload = entries;
	*out = entry;

	return 0;
}