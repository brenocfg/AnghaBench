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
struct tab {int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 scalar_t__ strcmp (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct tab *
lookup(struct tab *p, char *cmd)
{

	for (; p->name != NULL; p++)
		if (strcmp(cmd, p->name) == 0)
			return (p);
	return (0);
}