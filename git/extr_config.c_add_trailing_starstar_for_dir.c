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
struct strbuf {int len; int /*<<< orphan*/ * buf; } ;

/* Variables and functions */
 scalar_t__ is_dir_sep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char*) ; 

__attribute__((used)) static void add_trailing_starstar_for_dir(struct strbuf *pat)
{
	if (pat->len && is_dir_sep(pat->buf[pat->len - 1]))
		strbuf_addstr(pat, "**");
}