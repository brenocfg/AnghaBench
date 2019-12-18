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
struct TYPE_3__ {char* str; int value; } ;

/* Variables and functions */
 TYPE_1__* elftypes ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 size_t nitems (TYPE_1__*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
printelftypes(void)
{
	size_t elfwalk;

	fprintf(stderr, "known ELF types are: ");
	for (elfwalk = 0; elfwalk < nitems(elftypes); elfwalk++)
		fprintf(stderr, "%s(%u) ", elftypes[elfwalk].str,
		    elftypes[elfwalk].value);
	fprintf(stderr, "\n");
}