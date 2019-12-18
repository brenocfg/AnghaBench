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
struct archive {int /*<<< orphan*/  vtable; int /*<<< orphan*/  state; int /*<<< orphan*/  magic; } ;
struct archive_write {int bytes_per_block; int bytes_in_last_block; int null_length; unsigned char* nulls; struct archive archive; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_STATE_NEW ; 
 int /*<<< orphan*/  ARCHIVE_WRITE_MAGIC ; 
 int /*<<< orphan*/  archive_write_vtable () ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  free (struct archive_write*) ; 

struct archive *
archive_write_new(void)
{
	struct archive_write *a;
	unsigned char *nulls;

	a = (struct archive_write *)calloc(1, sizeof(*a));
	if (a == NULL)
		return (NULL);
	a->archive.magic = ARCHIVE_WRITE_MAGIC;
	a->archive.state = ARCHIVE_STATE_NEW;
	a->archive.vtable = archive_write_vtable();
	/*
	 * The value 10240 here matches the traditional tar default,
	 * but is otherwise arbitrary.
	 * TODO: Set the default block size from the format selected.
	 */
	a->bytes_per_block = 10240;
	a->bytes_in_last_block = -1;	/* Default */

	/* Initialize a block of nulls for padding purposes. */
	a->null_length = 1024;
	nulls = (unsigned char *)calloc(1, a->null_length);
	if (nulls == NULL) {
		free(a);
		return (NULL);
	}
	a->nulls = nulls;
	return (&a->archive);
}