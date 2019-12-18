#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int enabled; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* daemon_service ; 
 int /*<<< orphan*/  die (char*,char const*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void enable_service(const char *name, int ena)
{
	int i;
	for (i = 0; i < ARRAY_SIZE(daemon_service); i++) {
		if (!strcmp(daemon_service[i].name, name)) {
			daemon_service[i].enabled = ena;
			return;
		}
	}
	die("No such service %s", name);
}