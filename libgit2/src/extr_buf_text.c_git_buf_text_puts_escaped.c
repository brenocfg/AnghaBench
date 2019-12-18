#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* ptr; int size; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC_ADD (size_t*,size_t,int) ; 
 scalar_t__ git_buf_grow_by (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  memmove (char*,char const*,size_t) ; 
 size_t strcspn (char const*,char const*) ; 
 size_t strlen (char const*) ; 
 size_t strspn (char const*,char const*) ; 

int git_buf_text_puts_escaped(
	git_buf *buf,
	const char *string,
	const char *esc_chars,
	const char *esc_with)
{
	const char *scan;
	size_t total = 0, esc_len = strlen(esc_with), count, alloclen;

	if (!string)
		return 0;

	for (scan = string; *scan; ) {
		/* count run of non-escaped characters */
		count = strcspn(scan, esc_chars);
		total += count;
		scan += count;
		/* count run of escaped characters */
		count = strspn(scan, esc_chars);
		total += count * (esc_len + 1);
		scan += count;
	}

	GIT_ERROR_CHECK_ALLOC_ADD(&alloclen, total, 1);
	if (git_buf_grow_by(buf, alloclen) < 0)
		return -1;

	for (scan = string; *scan; ) {
		count = strcspn(scan, esc_chars);

		memmove(buf->ptr + buf->size, scan, count);
		scan += count;
		buf->size += count;

		for (count = strspn(scan, esc_chars); count > 0; --count) {
			/* copy escape sequence */
			memmove(buf->ptr + buf->size, esc_with, esc_len);
			buf->size += esc_len;
			/* copy character to be escaped */
			buf->ptr[buf->size] = *scan;
			buf->size++;
			scan++;
		}
	}

	buf->ptr[buf->size] = '\0';

	return 0;
}