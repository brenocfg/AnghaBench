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
struct atom_value {int /*<<< orphan*/ * s; } ;

/* Variables and functions */
 int used_atom_cnt ; 
 int /*<<< orphan*/ * xstrdup (char*) ; 

__attribute__((used)) static void fill_missing_values(struct atom_value *val)
{
	int i;
	for (i = 0; i < used_atom_cnt; i++) {
		struct atom_value *v = &val[i];
		if (v->s == NULL)
			v->s = xstrdup("");
	}
}