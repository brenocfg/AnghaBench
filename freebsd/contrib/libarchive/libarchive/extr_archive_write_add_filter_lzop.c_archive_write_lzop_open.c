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
struct write_lzop {char compression_level; int /*<<< orphan*/  pdata; } ;
struct archive_write_filter {scalar_t__ data; } ;
struct archive_string {int /*<<< orphan*/  s; } ;

/* Variables and functions */
 int __archive_write_program_open (struct archive_write_filter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_strappend_char (struct archive_string*,char) ; 
 int /*<<< orphan*/  archive_strcpy (struct archive_string*,char*) ; 
 int /*<<< orphan*/  archive_string_free (struct archive_string*) ; 
 int /*<<< orphan*/  archive_string_init (struct archive_string*) ; 

__attribute__((used)) static int
archive_write_lzop_open(struct archive_write_filter *f)
{
	struct write_lzop *data = (struct write_lzop *)f->data;
	struct archive_string as;
	int r;

	archive_string_init(&as);
	archive_strcpy(&as, "lzop");
	/* Specify compression level. */
	if (data->compression_level > 0) {
		archive_strappend_char(&as, ' ');
		archive_strappend_char(&as, '-');
		archive_strappend_char(&as, '0' + data->compression_level);
	}

	r = __archive_write_program_open(f, data->pdata, as.s);
	archive_string_free(&as);
	return (r);
}