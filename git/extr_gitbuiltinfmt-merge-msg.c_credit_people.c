#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct string_list {int nr; TYPE_1__* items; } ;
struct strbuf {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  string; } ;

/* Variables and functions */
 int /*<<< orphan*/  IDENT_NO_DATE ; 
 int /*<<< orphan*/  add_people_count (struct strbuf*,struct string_list*) ; 
 int /*<<< orphan*/  comment_line_char ; 
 char* git_author_info (int /*<<< orphan*/ ) ; 
 char* git_committer_info (int /*<<< orphan*/ ) ; 
 scalar_t__ skip_prefix (char const*,int /*<<< orphan*/ ,char const**) ; 
 scalar_t__ starts_with (char const*,char*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void credit_people(struct strbuf *out,
			  struct string_list *them,
			  int kind)
{
	const char *label;
	const char *me;

	if (kind == 'a') {
		label = "By";
		me = git_author_info(IDENT_NO_DATE);
	} else {
		label = "Via";
		me = git_committer_info(IDENT_NO_DATE);
	}

	if (!them->nr ||
	    (them->nr == 1 &&
	     me &&
	     skip_prefix(me, them->items->string, &me) &&
	     starts_with(me, " <")))
		return;
	strbuf_addf(out, "\n%c %s ", comment_line_char, label);
	add_people_count(out, them);
}