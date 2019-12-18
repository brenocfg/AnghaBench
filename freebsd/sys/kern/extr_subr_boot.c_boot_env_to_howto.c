#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int mask; int /*<<< orphan*/ * ev; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (char*) ; 
 char* GETENV (int /*<<< orphan*/ *) ; 
 TYPE_1__* howto_names ; 
 scalar_t__ strcasecmp (char*,char*) ; 

int
boot_env_to_howto(void)
{
	int i, howto;
	char *val;

	for (howto = 0, i = 0; howto_names[i].ev != NULL; i++) {
		val = GETENV(howto_names[i].ev);
		if (val != NULL && strcasecmp(val, "no") != 0)
			howto |= howto_names[i].mask;
		FREE(val);
	}
	return (howto);
}