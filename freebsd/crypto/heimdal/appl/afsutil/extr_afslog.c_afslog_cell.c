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
struct cell_list {char const* cell; struct cell_list* next; } ;

/* Variables and functions */
 struct cell_list* cell_list ; 
 char* expand_cell_name (char const*) ; 
 int /*<<< orphan*/  free (struct cell_list*) ; 
 struct cell_list* malloc (int) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 char const* strdup (char const*) ; 
 scalar_t__ verbose ; 
 int /*<<< orphan*/  warnx (char*,char const*,...) ; 

__attribute__((used)) static int
afslog_cell(const char *cell, int expand)
{
    struct cell_list *p, **q;
    const char *c = cell;
    if(expand){
	c = expand_cell_name(cell);
	if(c == NULL){
	    warnx("No cell matching \"%s\" found.", cell);
	    return -1;
	}
	if(verbose && strcmp(c, cell) != 0)
	    warnx("Cell \"%s\" expanded to \"%s\"", cell, c);
    }
    /* add to list of cells to get tokens for, and also remove
       duplicates; the actual afslog takes place later */
    for(p = cell_list, q = &cell_list; p; q = &p->next, p = p->next)
	if(strcmp(p->cell, c) == 0)
	    return 0;
    p = malloc(sizeof(*p));
    if(p == NULL)
	return -1;
    p->cell = strdup(c);
    if(p->cell == NULL) {
	free(p);
	return -1;
    }
    p->next = NULL;
    *q = p;
    return 0;
}