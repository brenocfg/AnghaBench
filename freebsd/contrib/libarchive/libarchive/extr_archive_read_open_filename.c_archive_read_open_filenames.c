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
struct TYPE_2__ {int /*<<< orphan*/  m; } ;
struct read_file_data {size_t block_size; int fd; int /*<<< orphan*/  filename_type; scalar_t__ use_lseek; scalar_t__ st_mode; int /*<<< orphan*/ * buffer; TYPE_1__ filename; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 scalar_t__ ARCHIVE_OK ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  FNT_MBS ; 
 int /*<<< orphan*/  FNT_STDIN ; 
 int /*<<< orphan*/  archive_clear_error (struct archive*) ; 
 scalar_t__ archive_read_append_callback_data (struct archive*,struct read_file_data*) ; 
 int archive_read_open1 (struct archive*) ; 
 int /*<<< orphan*/  archive_read_set_close_callback (struct archive*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_read_set_open_callback (struct archive*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_read_set_read_callback (struct archive*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_read_set_seek_callback (struct archive*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_read_set_skip_callback (struct archive*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_read_set_switch_callback (struct archive*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_set_error (struct archive*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ calloc (int,scalar_t__) ; 
 int /*<<< orphan*/  file_close ; 
 int /*<<< orphan*/  file_open ; 
 int /*<<< orphan*/  file_read ; 
 int /*<<< orphan*/  file_seek ; 
 int /*<<< orphan*/  file_skip ; 
 int /*<<< orphan*/  file_switch ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ strlen (char const*) ; 

int
archive_read_open_filenames(struct archive *a, const char **filenames,
    size_t block_size)
{
	struct read_file_data *mine;
	const char *filename = NULL;
	if (filenames)
		filename = *(filenames++);

	archive_clear_error(a);
	do
	{
		if (filename == NULL)
			filename = "";
		mine = (struct read_file_data *)calloc(1,
			sizeof(*mine) + strlen(filename));
		if (mine == NULL)
			goto no_memory;
		strcpy(mine->filename.m, filename);
		mine->block_size = block_size;
		mine->fd = -1;
		mine->buffer = NULL;
		mine->st_mode = mine->use_lseek = 0;
		if (filename == NULL || filename[0] == '\0') {
			mine->filename_type = FNT_STDIN;
		} else
			mine->filename_type = FNT_MBS;
		if (archive_read_append_callback_data(a, mine) != (ARCHIVE_OK))
			return (ARCHIVE_FATAL);
		if (filenames == NULL)
			break;
		filename = *(filenames++);
	} while (filename != NULL && filename[0] != '\0');
	archive_read_set_open_callback(a, file_open);
	archive_read_set_read_callback(a, file_read);
	archive_read_set_skip_callback(a, file_skip);
	archive_read_set_close_callback(a, file_close);
	archive_read_set_switch_callback(a, file_switch);
	archive_read_set_seek_callback(a, file_seek);

	return (archive_read_open1(a));
no_memory:
	archive_set_error(a, ENOMEM, "No memory");
	return (ARCHIVE_FATAL);
}