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
struct TYPE_3__ {char* name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 TYPE_1__* types ; 

__attribute__((used)) static int usage(const char *progname)
{
	int i;

	fprintf(stderr, "Usage: %s <hash type> [<file>...]\n"
		"Supported hash types:", progname);

	for (i = 0; i < ARRAY_SIZE(types); i++)
		fprintf(stderr, "%s %s", i ? "," : "", types[i].name);

	fprintf(stderr, "\n");
	return 1;
}