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
struct togglelist {char* name; char* help; } ;

/* Variables and functions */
 struct togglelist* Togglelist ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static int
togglehelp(void)
{
    struct togglelist *c;

    for (c = Togglelist; c->name; c++) {
	if (c->help) {
	    if (*c->help)
		printf("%-15s toggle %s\n", c->name, c->help);
	    else
		printf("\n");
	}
    }
    printf("\n");
    printf("%-15s %s\n", "?", "display help information");
    return 0;
}