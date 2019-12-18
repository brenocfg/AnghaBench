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
struct shar {int /*<<< orphan*/  quoted_name; int /*<<< orphan*/  work; struct shar* last_dir; int /*<<< orphan*/  entry; } ;
struct archive_write {int /*<<< orphan*/ * format_data; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  archive_entry_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_string_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct shar*) ; 

__attribute__((used)) static int
archive_write_shar_free(struct archive_write *a)
{
	struct shar *shar;

	shar = (struct shar *)a->format_data;
	if (shar == NULL)
		return (ARCHIVE_OK);

	archive_entry_free(shar->entry);
	free(shar->last_dir);
	archive_string_free(&(shar->work));
	archive_string_free(&(shar->quoted_name));
	free(shar);
	a->format_data = NULL;
	return (ARCHIVE_OK);
}