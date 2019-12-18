#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ v_abrev; scalar_t__ v_name; } ;
typedef  TYPE_1__ value_t ;

/* Variables and functions */
 scalar_t__ equal (scalar_t__,char*) ; 
 TYPE_1__* vtable ; 

__attribute__((used)) static value_t *
vlookup(char *s)
{
	value_t *p;

	for (p = vtable; p->v_name; p++)
		if (equal(p->v_name, s) || (p->v_abrev && equal(p->v_abrev, s)))
			return (p);
	return (NULL);
}