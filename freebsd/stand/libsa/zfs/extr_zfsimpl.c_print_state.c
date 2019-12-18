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
typedef  int /*<<< orphan*/  vdev_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  STATUS_FORMAT ; 
 int pager_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  state_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 

__attribute__((used)) static int
print_state(int indent, const char *name, vdev_state_t state)
{
	char buf[512];
	int i;

	buf[0] = 0;
	for (i = 0; i < indent; i++)
		strcat(buf, "  ");
	strcat(buf, name);

	return (pager_printf(STATUS_FORMAT, buf, state_name(state)));
}