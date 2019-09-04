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
struct strbuf {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 scalar_t__ starts_with (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strbuf_insert (struct strbuf*,int /*<<< orphan*/ ,char*,int) ; 

void expand_notes_ref(struct strbuf *sb)
{
	if (starts_with(sb->buf, "refs/notes/"))
		return; /* we're happy */
	else if (starts_with(sb->buf, "notes/"))
		strbuf_insert(sb, 0, "refs/", 5);
	else
		strbuf_insert(sb, 0, "refs/notes/", 11);
}