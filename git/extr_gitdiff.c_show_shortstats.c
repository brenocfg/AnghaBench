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
struct diffstat_t {int nr; TYPE_1__** files; } ;
struct diff_options {int dummy; } ;
struct TYPE_2__ {int added; int deleted; int /*<<< orphan*/  is_binary; int /*<<< orphan*/  is_interesting; scalar_t__ is_unmerged; } ;

/* Variables and functions */
 int /*<<< orphan*/  print_stat_summary_inserts_deletes (struct diff_options*,int,int,int) ; 

__attribute__((used)) static void show_shortstats(struct diffstat_t *data, struct diff_options *options)
{
	int i, adds = 0, dels = 0, total_files = data->nr;

	if (data->nr == 0)
		return;

	for (i = 0; i < data->nr; i++) {
		int added = data->files[i]->added;
		int deleted = data->files[i]->deleted;

		if (data->files[i]->is_unmerged ||
		    (!data->files[i]->is_interesting && (added + deleted == 0))) {
			total_files--;
		} else if (!data->files[i]->is_binary) { /* don't count bytes */
			adds += added;
			dels += deleted;
		}
	}
	print_stat_summary_inserts_deletes(options, total_files, adds, dels);
}