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
struct warc_s {scalar_t__ typ; size_t populz; } ;
struct archive_write {struct warc_s* format_data; } ;
typedef  int ssize_t ;

/* Variables and functions */
 scalar_t__ AE_IFREG ; 
 int ARCHIVE_OK ; 
 int __archive_write_output (struct archive_write*,void const*,size_t) ; 

__attribute__((used)) static ssize_t
_warc_data(struct archive_write *a, const void *buf, size_t len)
{
	struct warc_s *w = a->format_data;

	if (w->typ == AE_IFREG) {
		int rc;

		/* never write more bytes than announced */
		if (len > w->populz) {
			len = (size_t)w->populz;
		}

		/* now then, out we put the whole shebang */
		rc = __archive_write_output(a, buf, len);
		if (rc != ARCHIVE_OK) {
			return rc;
		}
	}
	return len;
}