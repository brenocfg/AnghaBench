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
struct name {struct name* n_blink; struct name* n_flink; } ;

/* Variables and functions */
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (scalar_t__) ; 
 struct name* nalloc (char*,int) ; 
 scalar_t__ strlen (char*) ; 
 char* yankword (char*,char*) ; 

struct name *
extract(char *line, int ntype)
{
	char *cp, *nbuf;
	struct name *top, *np, *t;

	if (line == NULL || *line == '\0')
		return (NULL);
	if ((nbuf = malloc(strlen(line) + 1)) == NULL)
		err(1, "Out of memory");
	top = NULL;
	np = NULL;
	cp = line;
	while ((cp = yankword(cp, nbuf)) != NULL) {
		t = nalloc(nbuf, ntype);
		if (top == NULL)
			top = t;
		else
			np->n_flink = t;
		t->n_blink = np;
		np = t;
	}
	(void)free(nbuf);
	return (top);
}