#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  s; } ;
struct archive {TYPE_1__ error_string; int /*<<< orphan*/  error; int /*<<< orphan*/  archive_error_number; } ;

/* Variables and functions */
 int /*<<< orphan*/  archive_string_copy (TYPE_1__*,TYPE_1__*) ; 

void
archive_copy_error(struct archive *dest, struct archive *src)
{
	dest->archive_error_number = src->archive_error_number;

	archive_string_copy(&dest->error_string, &src->error_string);
	dest->error = dest->error_string.s;
}