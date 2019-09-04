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

/* Variables and functions */
 int interpret_branch_name (char const*,int,struct strbuf*,unsigned int) ; 
 int /*<<< orphan*/  strbuf_add (struct strbuf*,char const*,int) ; 
 int strlen (char const*) ; 

void strbuf_branchname(struct strbuf *sb, const char *name, unsigned allowed)
{
	int len = strlen(name);
	int used = interpret_branch_name(name, len, sb, allowed);

	if (used < 0)
		used = 0;
	strbuf_add(sb, name + used, len - used);
}