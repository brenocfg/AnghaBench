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
struct strbuf {size_t alloc; int /*<<< orphan*/  buf; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 scalar_t__ ERANGE ; 
 size_t STRBUF_MAXLINK ; 
 scalar_t__ errno ; 
 size_t readlink (char const*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  strbuf_grow (struct strbuf*,size_t) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,size_t) ; 

int strbuf_readlink(struct strbuf *sb, const char *path, size_t hint)
{
	size_t oldalloc = sb->alloc;

	if (hint < 32)
		hint = 32;

	while (hint < STRBUF_MAXLINK) {
		ssize_t len;

		strbuf_grow(sb, hint);
		len = readlink(path, sb->buf, hint);
		if (len < 0) {
			if (errno != ERANGE)
				break;
		} else if (len < hint) {
			strbuf_setlen(sb, len);
			return 0;
		}

		/* .. the buffer was too small - try again */
		hint *= 2;
	}
	if (oldalloc == 0)
		strbuf_release(sb);
	return -1;
}