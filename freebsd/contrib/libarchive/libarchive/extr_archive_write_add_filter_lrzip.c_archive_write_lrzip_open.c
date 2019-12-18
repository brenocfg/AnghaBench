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
struct write_lrzip {int compression; scalar_t__ compression_level; int /*<<< orphan*/  pdata; } ;
struct archive_write_filter {scalar_t__ data; } ;
struct archive_string {int /*<<< orphan*/  s; } ;

/* Variables and functions */
 int __archive_write_program_open (struct archive_write_filter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_strappend_char (struct archive_string*,scalar_t__) ; 
 int /*<<< orphan*/  archive_strcat (struct archive_string*,char*) ; 
 int /*<<< orphan*/  archive_strcpy (struct archive_string*,char*) ; 
 int /*<<< orphan*/  archive_string_free (struct archive_string*) ; 
 int /*<<< orphan*/  archive_string_init (struct archive_string*) ; 
#define  bzip2 133 
#define  gzip 132 
#define  lzma 131 
#define  lzo 130 
#define  none 129 
#define  zpaq 128 

__attribute__((used)) static int
archive_write_lrzip_open(struct archive_write_filter *f)
{
	struct write_lrzip *data = (struct write_lrzip *)f->data;
	struct archive_string as;
	int r;

	archive_string_init(&as);
	archive_strcpy(&as, "lrzip -q");

	/* Specify compression type. */
	switch (data->compression) {
	case lzma:/* default compression */
		break;
	case bzip2:
		archive_strcat(&as, " -b");
		break;
	case gzip:
		archive_strcat(&as, " -g");
		break;
	case lzo:
		archive_strcat(&as, " -l");
		break;
	case none:
		archive_strcat(&as, " -n");
		break;
	case zpaq:
		archive_strcat(&as, " -z");
		break;
	}

	/* Specify compression level. */
	if (data->compression_level > 0) {
		archive_strcat(&as, " -L ");
		archive_strappend_char(&as, '0' + data->compression_level);
	}

	r = __archive_write_program_open(f, data->pdata, as.s);
	archive_string_free(&as);
	return (r);
}