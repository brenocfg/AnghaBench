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
struct rev_info {int dummy; } ;
struct commit {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 char* get_revision_mark (struct rev_info const*,struct commit const*) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strlen (char*) ; 

void put_revision_mark(const struct rev_info *revs, const struct commit *commit)
{
	char *mark = get_revision_mark(revs, commit);
	if (!strlen(mark))
		return;
	fputs(mark, stdout);
	putchar(' ');
}