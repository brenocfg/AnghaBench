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
struct archive_read {int /*<<< orphan*/  archive; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_ERRNO_FILE_FORMAT ; 
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int H_SIZE ; 
 void* __archive_read_ahead (struct archive_read*,int,int*) ; 
 int /*<<< orphan*/  __archive_read_consume (struct archive_read*,size_t) ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 size_t lha_check_header_format (char const*) ; 

__attribute__((used)) static int
lha_skip_sfx(struct archive_read *a)
{
	const void *h;
	const char *p, *q;
	size_t next, skip;
	ssize_t bytes, window;

	window = 4096;
	for (;;) {
		h = __archive_read_ahead(a, window, &bytes);
		if (h == NULL) {
			/* Remaining bytes are less than window. */
			window >>= 1;
			if (window < (H_SIZE + 3))
				goto fatal;
			continue;
		}
		if (bytes < H_SIZE)
			goto fatal;
		p = h;
		q = p + bytes;

		/*
		 * Scan ahead until we find something that looks
		 * like the lha header.
		 */
		while (p + H_SIZE < q) {
			if ((next = lha_check_header_format(p)) == 0) {
				skip = p - (const char *)h;
				__archive_read_consume(a, skip);
				return (ARCHIVE_OK);
			}
			p += next;
		}
		skip = p - (const char *)h;
		__archive_read_consume(a, skip);
	}
fatal:
	archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
	    "Couldn't find out LHa header");
	return (ARCHIVE_FATAL);
}