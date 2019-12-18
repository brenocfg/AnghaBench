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
struct grep_pat {int dummy; } ;
typedef  int /*<<< orphan*/  regmatch_t ;

/* Variables and functions */

__attribute__((used)) static int pcre1match(struct grep_pat *p, const char *line, const char *eol,
		regmatch_t *match, int eflags)
{
	return 1;
}