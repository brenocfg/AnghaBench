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
typedef  int /*<<< orphan*/  cell ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 char** realloc (char**,int) ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strdup (char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static void
find_cells(const char *file, char ***cells, int *idx)
{
    FILE *f;
    char cell[64];
    int i;
    int ind = *idx;

    f = fopen(file, "r");
    if (f == NULL)
	return;
    while (fgets(cell, sizeof(cell), f)) {
	char *t;
	t = cell + strlen(cell);
	for (; t >= cell; t--)
	  if (*t == '\n' || *t == '\t' || *t == ' ')
	    *t = 0;
	if (cell[0] == '\0' || cell[0] == '#')
	    continue;
	for(i = 0; i < ind; i++)
	    if(strcmp((*cells)[i], cell) == 0)
		break;
	if(i == ind){
	    char **tmp;

	    tmp = realloc(*cells, (ind + 1) * sizeof(**cells));
	    if (tmp == NULL)
		break;
	    *cells = tmp;
	    (*cells)[ind] = strdup(cell);
	    if ((*cells)[ind] == NULL)
		break;
	    ++ind;
	}
    }
    fclose(f);
    *idx = ind;
}