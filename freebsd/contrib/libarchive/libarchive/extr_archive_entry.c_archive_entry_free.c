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
struct archive_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  archive_entry_clear (struct archive_entry*) ; 
 int /*<<< orphan*/  free (struct archive_entry*) ; 

void
archive_entry_free(struct archive_entry *entry)
{
	archive_entry_clear(entry);
	free(entry);
}