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
struct strbuf {size_t alloc; size_t len; scalar_t__ buf; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  strbuf_grow (struct strbuf*,size_t) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,scalar_t__) ; 
 scalar_t__ xread (int,scalar_t__,size_t) ; 

ssize_t strbuf_read_once(struct strbuf *sb, int fd, size_t hint)
{
	size_t oldalloc = sb->alloc;
	ssize_t cnt;

	strbuf_grow(sb, hint ? hint : 8192);
	cnt = xread(fd, sb->buf + sb->len, sb->alloc - sb->len - 1);
	if (cnt > 0)
		strbuf_setlen(sb, sb->len + cnt);
	else if (oldalloc == 0)
		strbuf_release(sb);
	return cnt;
}