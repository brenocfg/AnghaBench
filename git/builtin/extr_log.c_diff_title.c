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
struct strbuf {char const* buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char const*,int) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 

__attribute__((used)) static const char *diff_title(struct strbuf *sb, int reroll_count,
		       const char *generic, const char *rerolled)
{
	if (reroll_count <= 0)
		strbuf_addstr(sb, generic);
	else /* RFC may be v0, so allow -v1 to diff against v0 */
		strbuf_addf(sb, rerolled, reroll_count - 1);
	return sb->buf;
}