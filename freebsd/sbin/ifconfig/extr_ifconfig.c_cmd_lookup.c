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
struct cmd {scalar_t__ c_iscloneop; int /*<<< orphan*/  c_name; struct cmd* c_next; } ;

/* Variables and functions */
 struct cmd* cmds ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct cmd *
cmd_lookup(const char *name, int iscreate)
{
	const struct cmd *p;

	for (p = cmds; p != NULL; p = p->c_next)
		if (strcmp(name, p->c_name) == 0) {
			if (iscreate) {
				if (p->c_iscloneop)
					return p;
			} else {
				if (!p->c_iscloneop)
					return p;
			}
		}
	return NULL;
}