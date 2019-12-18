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
struct archive {scalar_t__ archive_error_number; int /*<<< orphan*/ * error; int /*<<< orphan*/  error_string; } ;

/* Variables and functions */
 int /*<<< orphan*/  archive_string_empty (int /*<<< orphan*/ *) ; 

void
archive_clear_error(struct archive *a)
{
	archive_string_empty(&a->error_string);
	a->error = NULL;
	a->archive_error_number = 0;
}