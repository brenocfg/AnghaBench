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
struct macro_definition {int type; char* defn; } ;

/* Variables and functions */
 int MACRTYPE ; 
 int TYPEMASK ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,char const*,char*) ; 
 scalar_t__ mimic_gnu ; 
 scalar_t__ stderr ; 
 scalar_t__ traceout ; 

__attribute__((used)) static void
dump_one_def(const char *name, struct macro_definition *p)
{
	if (!traceout)
		traceout = stderr;
	if (mimic_gnu) {
		if ((p->type & TYPEMASK) == MACRTYPE)
			fprintf(traceout, "%s:\t%s\n", name, p->defn);
		else {
			fprintf(traceout, "%s:\t<%s>\n", name, p->defn);
		}
	} else
		fprintf(traceout, "`%s'\t`%s'\n", name, p->defn);
}