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
typedef  int /*<<< orphan*/  varbuf ;
struct var {int /*<<< orphan*/  v_name; struct var* v_link; } ;

/* Variables and functions */
 int BUFSIZ ; 
 int HSHSIZE ; 
 int /*<<< orphan*/  assign (char*,char*) ; 
 scalar_t__ equal (char*,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ salloc (int) ; 
 int /*<<< orphan*/  sort (char**) ; 
 char* value (char*) ; 
 struct var** variables ; 

int
set(void *v)
{
	char **arglist = v;
	struct var *vp;
	char *cp, *cp2;
	char varbuf[BUFSIZ], **ap, **p;
	int errs, h, s;

	if (*arglist == NULL) {
		for (h = 0, s = 1; h < HSHSIZE; h++)
			for (vp = variables[h]; vp != NULL; vp = vp->v_link)
				s++;
		ap = (char **)salloc(s * sizeof(*ap));
		for (h = 0, p = ap; h < HSHSIZE; h++)
			for (vp = variables[h]; vp != NULL; vp = vp->v_link)
				*p++ = vp->v_name;
		*p = NULL;
		sort(ap);
		for (p = ap; *p != NULL; p++)
			printf("%s\t%s\n", *p, value(*p));
		return (0);
	}
	errs = 0;
	for (ap = arglist; *ap != NULL; ap++) {
		cp = *ap;
		cp2 = varbuf;
		while (cp2 < varbuf + sizeof(varbuf) - 1 && *cp != '=' && *cp != '\0')
			*cp2++ = *cp++;
		*cp2 = '\0';
		if (*cp == '\0')
			cp = "";
		else
			cp++;
		if (equal(varbuf, "")) {
			printf("Non-null variable name required\n");
			errs++;
			continue;
		}
		assign(varbuf, cp);
	}
	return (errs);
}