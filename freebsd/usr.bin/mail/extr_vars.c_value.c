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
struct var {char* v_value; } ;

/* Variables and functions */
 char* getenv (char const*) ; 
 struct var* lookup (char const*) ; 

char *
value(const char *name)
{
	struct var *vp;

	if ((vp = lookup(name)) == NULL)
		return (getenv(name));
	return (vp->v_value);
}