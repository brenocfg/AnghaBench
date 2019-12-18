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
struct macro_definition {char* defn; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/ * ndptr ;

/* Variables and functions */
 int /*<<< orphan*/  eval (char const**,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_traced (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lookup (char const*) ; 
 int /*<<< orphan*/  m4errx (int,char*,char const*) ; 
 struct macro_definition* macro_getdef (int /*<<< orphan*/ *) ; 

void
doindir(const char *argv[], int argc)
{
	ndptr n;
	struct macro_definition *p = NULL;

	n = lookup(argv[2]);
	if (n == NULL || (p = macro_getdef(n)) == NULL)
		m4errx(1, "indir: undefined macro %s.", argv[2]);
	argv[1] = p->defn;

	eval(argv+1, argc-1, p->type, is_traced(n));
}