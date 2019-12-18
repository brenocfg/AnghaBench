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
struct var {void* v_value; struct var* v_link; void* v_name; } ;

/* Variables and functions */
 struct var* calloc (int,int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int hash (char const*) ; 
 struct var* lookup (char const*) ; 
 struct var** variables ; 
 void* vcopy (char const*) ; 
 int /*<<< orphan*/  vfree (void*) ; 

void
assign(const char *name, const char *value)
{
	struct var *vp;
	int h;

	h = hash(name);
	vp = lookup(name);
	if (vp == NULL) {
		if ((vp = calloc(1, sizeof(*vp))) == NULL)
			err(1, "Out of memory");
		vp->v_name = vcopy(name);
		vp->v_link = variables[h];
		variables[h] = vp;
	}
	else
		vfree(vp->v_value);
	vp->v_value = vcopy(value);
}