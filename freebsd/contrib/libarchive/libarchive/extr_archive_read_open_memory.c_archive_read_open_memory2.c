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
struct read_memory_data {unsigned char const* start; unsigned char const* p; unsigned char const* end; size_t read_size; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int archive_read_open1 (struct archive*) ; 
 int /*<<< orphan*/  archive_read_set_callback_data (struct archive*,struct read_memory_data*) ; 
 int /*<<< orphan*/  archive_read_set_close_callback (struct archive*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_read_set_open_callback (struct archive*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_read_set_read_callback (struct archive*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_read_set_seek_callback (struct archive*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_read_set_skip_callback (struct archive*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_set_error (struct archive*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  memory_read ; 
 int /*<<< orphan*/  memory_read_close ; 
 int /*<<< orphan*/  memory_read_open ; 
 int /*<<< orphan*/  memory_read_seek ; 
 int /*<<< orphan*/  memory_read_skip ; 

int
archive_read_open_memory2(struct archive *a, const void *buff,
    size_t size, size_t read_size)
{
	struct read_memory_data *mine;

	mine = (struct read_memory_data *)calloc(1, sizeof(*mine));
	if (mine == NULL) {
		archive_set_error(a, ENOMEM, "No memory");
		return (ARCHIVE_FATAL);
	}
	mine->start = mine->p = (const unsigned char *)buff;
	mine->end = mine->start + size;
	mine->read_size = read_size;
	archive_read_set_open_callback(a, memory_read_open);
	archive_read_set_read_callback(a, memory_read);
	archive_read_set_seek_callback(a, memory_read_seek);
	archive_read_set_skip_callback(a, memory_read_skip);
	archive_read_set_close_callback(a, memory_read_close);
	archive_read_set_callback_data(a, mine);
	return (archive_read_open1(a));
}