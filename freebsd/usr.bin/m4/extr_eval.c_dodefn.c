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
struct macro_definition {int type; int /*<<< orphan*/  defn; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILTIN_MARKER ; 
 int MACRTYPE ; 
 int TYPEMASK ; 
 struct macro_definition* lookup_macro_definition (char const*) ; 
 int /*<<< orphan*/  lquote ; 
 int /*<<< orphan*/  pbstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rquote ; 

__attribute__((used)) static void
dodefn(const char *name)
{
	struct macro_definition *p;

	if ((p = lookup_macro_definition(name)) != NULL) {
		if ((p->type & TYPEMASK) == MACRTYPE) {
			pbstr(rquote);
			pbstr(p->defn);
			pbstr(lquote);
		} else {
			pbstr(p->defn);
			pbstr(BUILTIN_MARKER);
		}
	}
}