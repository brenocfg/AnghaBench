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

/* Variables and functions */
 int ARCHIVE_EOF ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  BYTES_PER_BLOCK ; 
 int /*<<< orphan*/ * a ; 
 int /*<<< orphan*/  ae ; 
 int archive_read_close (int /*<<< orphan*/ *) ; 
 int archive_read_data_into_fd (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  archive_read_free (int /*<<< orphan*/ *) ; 
 int archive_read_next_header (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int archive_read_open_filename (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsdcat_print_error () ; 

void
bsdcat_read_to_stdout(const char* filename)
{
	int r;

	if (archive_read_open_filename(a, filename, BYTES_PER_BLOCK)
	    != ARCHIVE_OK)
		bsdcat_print_error();
	else if (r = archive_read_next_header(a, &ae),
		 r != ARCHIVE_OK && r != ARCHIVE_EOF)
		bsdcat_print_error();
	else if (r == ARCHIVE_EOF)
		/* for empty payloads don't try and read data */
		;
	else if (archive_read_data_into_fd(a, 1) != ARCHIVE_OK)
		bsdcat_print_error();
	if (archive_read_close(a) != ARCHIVE_OK)
		bsdcat_print_error();
	archive_read_free(a);
	a = NULL;
}