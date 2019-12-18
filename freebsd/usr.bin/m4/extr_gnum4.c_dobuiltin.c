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
typedef  int /*<<< orphan*/ * ndptr ;

/* Variables and functions */
 int /*<<< orphan*/  eval (char const**,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_traced (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m4errx (int,char*,char const*) ; 
 int /*<<< orphan*/  macro_builtin_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * macro_getbuiltin (char const*) ; 

void
dobuiltin(const char *argv[], int argc)
{
	ndptr p;

	argv[1] = NULL;
	p = macro_getbuiltin(argv[2]);
	if (p != NULL)
		eval(argv+1, argc-1, macro_builtin_type(p), is_traced(p));
	else
		m4errx(1, "unknown builtin %s.", argv[2]);
}