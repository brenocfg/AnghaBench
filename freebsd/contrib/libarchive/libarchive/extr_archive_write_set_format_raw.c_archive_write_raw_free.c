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
struct raw {int dummy; } ;
struct archive_write {int /*<<< orphan*/ * format_data; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  free (struct raw*) ; 

__attribute__((used)) static int
archive_write_raw_free(struct archive_write *a)
{
	struct raw *raw;

	raw = (struct raw *)a->format_data;
	free(raw);
	a->format_data = NULL;
	return (ARCHIVE_OK);
}