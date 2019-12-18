#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
struct TYPE_4__ {scalar_t__* c_cc; } ;
struct TYPE_3__ {scalar_t__* c_cc; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_2__ mode ; 
 TYPE_1__ oldmode ; 
 int /*<<< orphan*/  stderr ; 

void
report(const char *name, int which, u_int def)
{
	u_int old, new;

	new = mode.c_cc[which];
	old = oldmode.c_cc[which];

	if (old == new && old == def)
		return;

	(void)fprintf(stderr, "%s %s ", name, old == new ? "is" : "set to");

	if (new == 010)
		(void)fprintf(stderr, "backspace.\n");
	else if (new == 0177)
		(void)fprintf(stderr, "delete.\n");
	else if (new < 040) {
		new ^= 0100;
		(void)fprintf(stderr, "control-%c (^%c).\n", new, new);
	} else
		(void)fprintf(stderr, "%c.\n", new);
}