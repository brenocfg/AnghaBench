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
struct grep_pat {int /*<<< orphan*/  regexp; scalar_t__ pcre2_pattern; scalar_t__ pcre1_regexp; } ;
typedef  int /*<<< orphan*/  regmatch_t ;

/* Variables and functions */
 int /*<<< orphan*/  pcre1match (struct grep_pat*,char*,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pcre2match (struct grep_pat*,char*,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  regexec_buf (int /*<<< orphan*/ *,char*,int,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int patmatch(struct grep_pat *p, char *line, char *eol,
		    regmatch_t *match, int eflags)
{
	int hit;

	if (p->pcre1_regexp)
		hit = !pcre1match(p, line, eol, match, eflags);
	else if (p->pcre2_pattern)
		hit = !pcre2match(p, line, eol, match, eflags);
	else
		hit = !regexec_buf(&p->regexp, line, eol - line, 1, match,
				   eflags);

	return hit;
}