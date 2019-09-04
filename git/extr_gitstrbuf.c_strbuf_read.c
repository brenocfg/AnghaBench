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
struct strbuf {size_t len; size_t alloc; char* buf; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ read_in_full (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  strbuf_grow (struct strbuf*,int) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,size_t) ; 

ssize_t strbuf_read(struct strbuf *sb, int fd, size_t hint)
{
	size_t oldlen = sb->len;
	size_t oldalloc = sb->alloc;

	strbuf_grow(sb, hint ? hint : 8192);
	for (;;) {
		ssize_t want = sb->alloc - sb->len - 1;
		ssize_t got = read_in_full(fd, sb->buf + sb->len, want);

		if (got < 0) {
			if (oldalloc == 0)
				strbuf_release(sb);
			else
				strbuf_setlen(sb, oldlen);
			return -1;
		}
		sb->len += got;
		if (got < want)
			break;
		strbuf_grow(sb, 8192);
	}

	sb->buf[sb->len] = '\0';
	return sb->len - oldlen;
}