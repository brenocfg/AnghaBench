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
struct var {char const* v_name; struct var* v_link; } ;

/* Variables and functions */
 scalar_t__ equal (char const*,char const*) ; 
 size_t hash (char const*) ; 
 struct var** variables ; 

struct var *
lookup(const char *name)
{
	struct var *vp;

	for (vp = variables[hash(name)]; vp != NULL; vp = vp->v_link)
		if (*vp->v_name == *name && equal(vp->v_name, name))
			return (vp);
	return (NULL);
}