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
struct strbuf {int dummy; } ;
struct name_decoration {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ DECORATE_SHORT_REFS ; 
 scalar_t__ decoration_flags ; 
 int /*<<< orphan*/  prettify_refname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void show_name(struct strbuf *sb, const struct name_decoration *decoration)
{
	if (decoration_flags == DECORATE_SHORT_REFS)
		strbuf_addstr(sb, prettify_refname(decoration->name));
	else
		strbuf_addstr(sb, decoration->name);
}