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
struct TYPE_2__ {size_t entry_count; size_t expected_entry_count; unsigned int* expected_statuses; int /*<<< orphan*/  wrong_status_flags_count; int /*<<< orphan*/  wrong_sorted_path; int /*<<< orphan*/ * expected_paths; scalar_t__ debug; } ;
typedef  TYPE_1__ status_entry_counts ;

/* Variables and functions */
 int /*<<< orphan*/  cb_status__print (char const*,unsigned int,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

int cb_status__normal(
	const char *path, unsigned int status_flags, void *payload)
{
	status_entry_counts *counts = payload;

	if (counts->debug)
		cb_status__print(path, status_flags, NULL);

	if (counts->entry_count >= counts->expected_entry_count)
		counts->wrong_status_flags_count++;
	else if (strcmp(path, counts->expected_paths[counts->entry_count]))
		counts->wrong_sorted_path++;
	else if (status_flags != counts->expected_statuses[counts->entry_count])
		counts->wrong_status_flags_count++;

	counts->entry_count++;
	return 0;
}