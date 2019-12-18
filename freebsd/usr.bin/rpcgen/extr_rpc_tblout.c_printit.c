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

/* Variables and functions */
 int TABCOUNT ; 
 int TABSIZE ; 
 int TABSTOP ; 
 int /*<<< orphan*/  f_print (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fout ; 
 int fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  ptype (char const*,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ streq (char const*,char*) ; 
 char* stringfix (char const*) ; 
 int /*<<< orphan*/ * tabstr ; 

__attribute__((used)) static void
printit(const char *prefix, const char *type)
{
	int len;
	int tabs;


 	len = fprintf(fout, "\txdr_%s,", stringfix(type));
	/* account for leading tab expansion */
	len += TABSIZE - 1;
	/* round up to tabs required */
	tabs = (TABSTOP - len + TABSIZE - 1)/TABSIZE;
	f_print(fout, "%s", &tabstr[TABCOUNT-tabs]);

	if (streq(type, "void")) {
		f_print(fout, "0");
	} else {
		f_print(fout, "sizeof ( ");
		/* XXX: should "follow" be 1 ??? */
		ptype(prefix, type, 0);
		f_print(fout, ")");
	}
	f_print(fout, ",\n");
}