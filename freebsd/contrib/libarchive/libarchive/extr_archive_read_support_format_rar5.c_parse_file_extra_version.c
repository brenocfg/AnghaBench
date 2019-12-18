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
struct archive_string {char const* s; } ;
struct archive_read {int /*<<< orphan*/  archive; } ;
struct archive_entry {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int ARCHIVE_EOF ; 
 int /*<<< orphan*/  ARCHIVE_ERRNO_PROGRAMMER ; 
 int ARCHIVE_FATAL ; 
 scalar_t__ ARCHIVE_OK ; 
 char* archive_entry_pathname_utf8 (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_update_pathname_utf8 (struct archive_entry*,char const*) ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  archive_strcat (struct archive_string*,char const*) ; 
 int /*<<< orphan*/  archive_string_free (struct archive_string*) ; 
 int /*<<< orphan*/  archive_string_init (struct archive_string*) ; 
 int /*<<< orphan*/  archive_string_sprintf (struct archive_string*,char*,size_t) ; 
 scalar_t__ consume (struct archive_read*,size_t) ; 
 int /*<<< orphan*/  read_var_sized (struct archive_read*,size_t*,size_t*) ; 

__attribute__((used)) static int parse_file_extra_version(struct archive_read* a,
    struct archive_entry* e, ssize_t* extra_data_size)
{
	size_t flags = 0;
	size_t version = 0;
	size_t value_len = 0;
	struct archive_string version_string;
	struct archive_string name_utf8_string;

	/* Flags are ignored. */
	if(!read_var_sized(a, &flags, &value_len))
		return ARCHIVE_EOF;

	*extra_data_size -= value_len;
	if(ARCHIVE_OK != consume(a, value_len))
		return ARCHIVE_EOF;

	if(!read_var_sized(a, &version, &value_len))
		return ARCHIVE_EOF;

	*extra_data_size -= value_len;
	if(ARCHIVE_OK != consume(a, value_len))
		return ARCHIVE_EOF;

	/* extra_data_size should be zero here. */

	const char* cur_filename = archive_entry_pathname_utf8(e);
	if(cur_filename == NULL) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_PROGRAMMER,
		    "Version entry without file name");
		return ARCHIVE_FATAL;
	}

	archive_string_init(&version_string);
	archive_string_init(&name_utf8_string);

	/* Prepare a ;123 suffix for the filename, where '123' is the version
	 * value of this file. */
	archive_string_sprintf(&version_string, ";%zu", version);

	/* Build the new filename. */
	archive_strcat(&name_utf8_string, cur_filename);
	archive_strcat(&name_utf8_string, version_string.s);

	/* Apply the new filename into this file's context. */
	archive_entry_update_pathname_utf8(e, name_utf8_string.s);

	/* Free buffers. */
	archive_string_free(&version_string);
	archive_string_free(&name_utf8_string);
	return ARCHIVE_OK;
}