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
struct archive_read {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int H_SIZE ; 
 void* __archive_read_ahead (struct archive_read*,int,int*) ; 
 size_t lha_check_header_format (char const*) ; 

__attribute__((used)) static int
archive_read_format_lha_bid(struct archive_read *a, int best_bid)
{
	const char *p;
	const void *buff;
	ssize_t bytes_avail, offset, window;
	size_t next;

	/* If there's already a better bid than we can ever
	   make, don't bother testing. */
	if (best_bid > 30)
		return (-1);

	if ((p = __archive_read_ahead(a, H_SIZE, NULL)) == NULL)
		return (-1);

	if (lha_check_header_format(p) == 0)
		return (30);

	if (p[0] == 'M' && p[1] == 'Z') {
		/* PE file */
		offset = 0;
		window = 4096;
		while (offset < (1024 * 20)) {
			buff = __archive_read_ahead(a, offset + window,
			    &bytes_avail);
			if (buff == NULL) {
				/* Remaining bytes are less than window. */
				window >>= 1;
				if (window < (H_SIZE + 3))
					return (0);
				continue;
			}
			p = (const char *)buff + offset;
			while (p + H_SIZE < (const char *)buff + bytes_avail) {
				if ((next = lha_check_header_format(p)) == 0)
					return (30);
				p += next;
			}
			offset = p - (const char *)buff;
		}
	}
	return (0);
}