#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int level; struct TYPE_5__* ptnext; TYPE_1__* isoDirRecord; int /*<<< orphan*/ * parent; } ;
typedef  TYPE_2__ cd9660node ;
struct TYPE_4__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 

void
debug_print_path_tree(cd9660node *n)
{
	cd9660node *iterator = n;

	/* Only display this message when called with the root node */
	if (n->parent == NULL)
		printf("debug_print_path_table: Dumping path table contents\n");

	while (iterator != NULL) {
		if (iterator->isoDirRecord->name[0] == '\0')
			printf("0) (ROOT)\n");
		else
			printf("%i) %s\n", iterator->level,
			    iterator->isoDirRecord->name);

		iterator = iterator->ptnext;
	}
}