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
struct cmdnames {scalar_t__ cnt; struct cmdname** names; int /*<<< orphan*/  alloc; } ;
struct cmdname {int len; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (struct cmdname**,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FLEX_ALLOC_MEM (struct cmdname*,char const*,char const*,int) ; 

void add_cmdname(struct cmdnames *cmds, const char *name, int len)
{
	struct cmdname *ent;
	FLEX_ALLOC_MEM(ent, name, name, len);
	ent->len = len;

	ALLOC_GROW(cmds->names, cmds->cnt + 1, cmds->alloc);
	cmds->names[cmds->cnt++] = ent;
}