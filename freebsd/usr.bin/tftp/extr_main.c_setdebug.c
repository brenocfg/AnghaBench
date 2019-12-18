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
struct TYPE_2__ {char* name; char* desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  debug_find (char*) ; 
 char* debug_show (int /*<<< orphan*/ ) ; 
 TYPE_1__* debugs ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
setdebug(int argc, char *argv[])
{
	int i;

	if (argc != 1) {
		i = 1;
		while (i < argc)
			debug ^= debug_find(argv[i++]);
	}
	printf("The following debugging is enabled: %s\n", debug_show(debug));

	printf("\nThe following debugs are available:\n");
	i = 0;
	while (debugs[i].name != NULL) {
		printf("\t%s\t%s\n", debugs[i].name, debugs[i].desc);
		i++;
	}
}