#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int n; int parent; double d; char* name; } ;
typedef  TYPE_1__ knhx1_t ;
struct TYPE_6__ {int n; int max; int /*<<< orphan*/  error; TYPE_1__* node; } ;
typedef  TYPE_2__ knaux_t ;

/* Variables and functions */
 int /*<<< orphan*/  KNERR_BRACKET ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  isgraph (char) ; 
 scalar_t__ realloc (TYPE_1__*,int) ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 double strtod (char*,char**) ; 

__attribute__((used)) static inline char *add_node(const char *s, knaux_t *aux, int x)
{
	char *p, *nbeg, *nend = 0;
	knhx1_t *r;
	if (aux->n == aux->max) {
		aux->max = aux->max? aux->max<<1 : 8;
		aux->node = (knhx1_t*)realloc(aux->node, sizeof(knhx1_t) * aux->max);
	}
	r = aux->node + (aux->n++);
	r->n = x; r->parent = -1;
	for (p = (char*)s, nbeg = p, r->d = -1.0; *p && *p != ',' && *p != ')'; ++p) {
		if (*p == '[') {
			if (nend == 0) nend = p;
			do ++p; while (*p && *p != ']');
			if (*p == 0) {
				aux->error |= KNERR_BRACKET;
				break;
			}
		} else if (*p == ':') {
			if (nend == 0) nend = p;
			r->d = strtod(p + 1, &p);
			--p;
		} else if (!isgraph(*p)) if (nend == 0) nend = p;
	}
	if (nend == 0) nend = p;
	if (nend != nbeg) {
		r->name = (char*)calloc(nend - nbeg + 1, 1);
		strncpy(r->name, nbeg, nend - nbeg);
	} else r->name = strdup("");
	return p;
}