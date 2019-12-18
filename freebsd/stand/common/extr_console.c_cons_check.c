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
struct TYPE_2__ {char* c_name; } ;

/* Variables and functions */
 int cons_find (char*) ; 
 TYPE_1__** consoles ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* strdup (char const*) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static int
cons_check(const char *string)
{
    int		cons, found, failed;
    char	*curpos, *dup, *next;

    dup = next = strdup(string);
    found = failed = 0;
    while (next != NULL) {
	curpos = strsep(&next, " ,");
	if (*curpos != '\0') {
	    cons = cons_find(curpos);
	    if (cons == -1) {
		printf("console %s is invalid!\n", curpos);
		failed++;
	    } else {
		found++;
	    }
	}
    }

    free(dup);

    if (found == 0)
	printf("no valid consoles!\n");

    if (found == 0 || failed != 0) {
	printf("Available consoles:\n");
	for (cons = 0; consoles[cons] != NULL; cons++)
	    printf("    %s\n", consoles[cons]->c_name);
    }

    return (found);
}