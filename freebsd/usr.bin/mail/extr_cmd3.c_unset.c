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
struct var {int /*<<< orphan*/  v_value; int /*<<< orphan*/  v_name; struct var* v_link; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct var*) ; 
 scalar_t__ getenv (char*) ; 
 int hash (char*) ; 
 struct var* lookup (char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  sourcing ; 
 int /*<<< orphan*/  unsetenv (char*) ; 
 struct var** variables ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

int
unset(void *v)
{
	char **arglist = v;
	struct var *vp, *vp2;
	int errs, h;
	char **ap;

	errs = 0;
	for (ap = arglist; *ap != NULL; ap++) {
		if ((vp2 = lookup(*ap)) == NULL) {
			if (getenv(*ap)) 
				unsetenv(*ap);
			else if (!sourcing) {
				printf("\"%s\": undefined variable\n", *ap);
				errs++;
			}
			continue;
		}
		h = hash(*ap);
		if (vp2 == variables[h]) {
			variables[h] = variables[h]->v_link;
			vfree(vp2->v_name);
			vfree(vp2->v_value);
			(void)free(vp2);
			continue;
		}
		for (vp = variables[h]; vp->v_link != vp2; vp = vp->v_link)
			;
		vp->v_link = vp2->v_link;
		vfree(vp2->v_name);
		vfree(vp2->v_value);
		(void)free(vp2);
	}
	return (errs);
}