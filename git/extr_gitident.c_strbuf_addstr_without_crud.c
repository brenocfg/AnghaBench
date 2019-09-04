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
struct strbuf {unsigned char* buf; size_t len; } ;

/* Variables and functions */
 int /*<<< orphan*/  crud (unsigned char) ; 
 int /*<<< orphan*/  strbuf_grow (struct strbuf*,size_t) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static void strbuf_addstr_without_crud(struct strbuf *sb, const char *src)
{
	size_t i, len;
	unsigned char c;

	/* Remove crud from the beginning.. */
	while ((c = *src) != 0) {
		if (!crud(c))
			break;
		src++;
	}

	/* Remove crud from the end.. */
	len = strlen(src);
	while (len > 0) {
		c = src[len-1];
		if (!crud(c))
			break;
		--len;
	}

	/*
	 * Copy the rest to the buffer, but avoid the special
	 * characters '\n' '<' and '>' that act as delimiters on
	 * an identification line. We can only remove crud, never add it,
	 * so 'len' is our maximum.
	 */
	strbuf_grow(sb, len);
	for (i = 0; i < len; i++) {
		c = *src++;
		switch (c) {
		case '\n': case '<': case '>':
			continue;
		}
		sb->buf[sb->len++] = c;
	}
	sb->buf[sb->len] = '\0';
}