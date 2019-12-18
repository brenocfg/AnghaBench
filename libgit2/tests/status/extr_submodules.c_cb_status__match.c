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
struct TYPE_2__ {int /*<<< orphan*/ * expected_statuses; int /*<<< orphan*/  line; int /*<<< orphan*/  file; int /*<<< orphan*/ * expected_paths; int /*<<< orphan*/  entry_count; } ;
typedef  TYPE_1__ status_entry_counts ;

/* Variables and functions */
 int /*<<< orphan*/  clar__assert_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int cb_status__match(const char *p, unsigned int s, void *payload)
{
	status_entry_counts *counts = payload;
	int idx = counts->entry_count++;

	clar__assert_equal(
		counts->file, counts->line,
		"Status path mismatch", 1,
		"%s", counts->expected_paths[idx], p);

	clar__assert_equal(
		counts->file, counts->line,
		"Status code mismatch", 1,
		"%o", counts->expected_statuses[idx], s);

	return 0;
}