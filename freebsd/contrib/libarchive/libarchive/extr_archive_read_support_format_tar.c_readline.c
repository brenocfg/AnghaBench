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
struct TYPE_2__ {char* s; } ;
struct tar {TYPE_1__ line; } ;
struct archive_read {int /*<<< orphan*/  archive; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_ERRNO_FILE_FORMAT ; 
 int ARCHIVE_FATAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 void* __archive_read_ahead (struct archive_read*,int,int*) ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * archive_string_ensure (TYPE_1__*,int) ; 
 void* memchr (void const*,char,int) ; 
 int /*<<< orphan*/  memcpy (char*,void const*,int) ; 
 int /*<<< orphan*/  tar_flush_unconsumed (struct archive_read*,size_t*) ; 

__attribute__((used)) static ssize_t
readline(struct archive_read *a, struct tar *tar, const char **start,
    ssize_t limit, size_t *unconsumed)
{
	ssize_t bytes_read;
	ssize_t total_size = 0;
	const void *t;
	const char *s;
	void *p;

	tar_flush_unconsumed(a, unconsumed);

	t = __archive_read_ahead(a, 1, &bytes_read);
	if (bytes_read <= 0)
		return (ARCHIVE_FATAL);
	s = t;  /* Start of line? */
	p = memchr(t, '\n', bytes_read);
	/* If we found '\n' in the read buffer, return pointer to that. */
	if (p != NULL) {
		bytes_read = 1 + ((const char *)p) - s;
		if (bytes_read > limit) {
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "Line too long");
			return (ARCHIVE_FATAL);
		}
		*unconsumed = bytes_read;
		*start = s;
		return (bytes_read);
	}
	*unconsumed = bytes_read;
	/* Otherwise, we need to accumulate in a line buffer. */
	for (;;) {
		if (total_size + bytes_read > limit) {
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "Line too long");
			return (ARCHIVE_FATAL);
		}
		if (archive_string_ensure(&tar->line, total_size + bytes_read) == NULL) {
			archive_set_error(&a->archive, ENOMEM,
			    "Can't allocate working buffer");
			return (ARCHIVE_FATAL);
		}
		memcpy(tar->line.s + total_size, t, bytes_read);
		tar_flush_unconsumed(a, unconsumed);
		total_size += bytes_read;
		/* If we found '\n', clean up and return. */
		if (p != NULL) {
			*start = tar->line.s;
			return (total_size);
		}
		/* Read some more. */
		t = __archive_read_ahead(a, 1, &bytes_read);
		if (bytes_read <= 0)
			return (ARCHIVE_FATAL);
		s = t;  /* Start of line? */
		p = memchr(t, '\n', bytes_read);
		/* If we found '\n', trim the read. */
		if (p != NULL) {
			bytes_read = 1 + ((const char *)p) - s;
		}
		*unconsumed = bytes_read;
	}
}