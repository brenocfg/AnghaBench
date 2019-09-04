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
struct strbuf {scalar_t__ buf; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  strbuf_add (struct strbuf*,scalar_t__,size_t) ; 
 int /*<<< orphan*/  strbuf_add_wrapped_text (struct strbuf*,scalar_t__,int,int,int) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_swap (struct strbuf*,struct strbuf*) ; 

__attribute__((used)) static void strbuf_wrap(struct strbuf *sb, size_t pos,
			size_t width, size_t indent1, size_t indent2)
{
	struct strbuf tmp = STRBUF_INIT;

	if (pos)
		strbuf_add(&tmp, sb->buf, pos);
	strbuf_add_wrapped_text(&tmp, sb->buf + pos,
				(int) indent1, (int) indent2, (int) width);
	strbuf_swap(&tmp, sb);
	strbuf_release(&tmp);
}