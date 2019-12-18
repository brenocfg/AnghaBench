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
struct slclist {char* name; char* help; } ;

/* Variables and functions */
 struct slclist* SlcList ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
slc_help(void)
{
    struct slclist *c;

    for (c = SlcList; c->name; c++) {
	if (c->help) {
	    if (*c->help)
		printf("%-15s %s\n", c->name, c->help);
	    else
		printf("\n");
	}
    }
}