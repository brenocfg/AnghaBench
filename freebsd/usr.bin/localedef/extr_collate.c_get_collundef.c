#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char* name; int /*<<< orphan*/ * ref; } ;
typedef  TYPE_1__ collundef_t ;

/* Variables and functions */
 int NUM_WT ; 
 TYPE_1__* RB_FIND (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  RB_INSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  add_charmap_undefined (char*) ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  collundefs ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  new_pri () ; 
 int /*<<< orphan*/  stderr ; 
 char* strdup (char*) ; 

__attribute__((used)) static collundef_t *
get_collundef(char *name)
{
	collundef_t	srch;
	collundef_t	*ud;
	int		i;

	srch.name = name;
	if ((ud = RB_FIND(collundefs, &collundefs, &srch)) == NULL) {
		if (((ud = calloc(1, sizeof(*ud))) == NULL) ||
		    ((ud->name = strdup(name)) == NULL)) {
			fprintf(stderr,"out of memory");
			free(ud);
			return (NULL);
		}
		for (i = 0; i < NUM_WT; i++) {
			ud->ref[i] = new_pri();
		}
		RB_INSERT(collundefs, &collundefs, ud);
	}
	add_charmap_undefined(name);
	return (ud);
}