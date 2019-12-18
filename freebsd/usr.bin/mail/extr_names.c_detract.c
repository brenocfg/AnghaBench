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
struct name {int n_type; struct name* n_flink; int /*<<< orphan*/  n_name; } ;

/* Variables and functions */
 int GCOMMA ; 
 int GMASK ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 char* salloc (int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

char *
detract(struct name *np, int ntype)
{
	int s, comma;
	char *cp, *top;
	struct name *p;

	comma = ntype & GCOMMA;
	if (np == NULL)
		return (NULL);
	ntype &= ~GCOMMA;
	s = 0;
	if (debug && comma)
		fprintf(stderr, "detract asked to insert commas\n");
	for (p = np; p != NULL; p = p->n_flink) {
		if (ntype && (p->n_type & GMASK) != ntype)
			continue;
		s += strlen(p->n_name) + 1;
		if (comma)
			s++;
	}
	if (s == 0)
		return (NULL);
	s += 2;
	top = salloc(s);
	cp = top;
	for (p = np; p != NULL; p = p->n_flink) {
		if (ntype && (p->n_type & GMASK) != ntype)
			continue;
		cp += strlcpy(cp, p->n_name, strlen(p->n_name) + 1);
		if (comma && p->n_flink != NULL)
			*cp++ = ',';
		*cp++ = ' ';
	}
	*--cp = '\0';
	if (comma && *--cp == ',')
		*cp = '\0';
	return (top);
}