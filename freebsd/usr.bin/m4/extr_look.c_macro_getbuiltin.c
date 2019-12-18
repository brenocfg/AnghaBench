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
typedef  TYPE_1__* ndptr ;
struct TYPE_4__ {scalar_t__ builtin_type; } ;

/* Variables and functions */
 scalar_t__ MACRTYPE ; 
 TYPE_1__* lookup (char const*) ; 

ndptr
macro_getbuiltin(const char *name)
{
	ndptr p;

	p = lookup(name);
	if (p == NULL || p->builtin_type == MACRTYPE)
		return NULL;
	else
		return p;
}