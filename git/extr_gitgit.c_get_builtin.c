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
struct cmd_struct {int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct cmd_struct*) ; 
 struct cmd_struct* commands ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct cmd_struct *get_builtin(const char *s)
{
	int i;
	for (i = 0; i < ARRAY_SIZE(commands); i++) {
		struct cmd_struct *p = commands + i;
		if (!strcmp(s, p->cmd))
			return p;
	}
	return NULL;
}