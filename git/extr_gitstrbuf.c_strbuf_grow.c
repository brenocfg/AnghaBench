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
struct strbuf {size_t len; char* buf; int /*<<< orphan*/  alloc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (char*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die (char*) ; 
 scalar_t__ unsigned_add_overflows (size_t,size_t) ; 

void strbuf_grow(struct strbuf *sb, size_t extra)
{
	int new_buf = !sb->alloc;
	if (unsigned_add_overflows(extra, 1) ||
	    unsigned_add_overflows(sb->len, extra + 1))
		die("you want to use way too much memory");
	if (new_buf)
		sb->buf = NULL;
	ALLOC_GROW(sb->buf, sb->len + extra + 1, sb->alloc);
	if (new_buf)
		sb->buf[0] = '\0';
}