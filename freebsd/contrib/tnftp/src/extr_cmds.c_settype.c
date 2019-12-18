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
struct types {int /*<<< orphan*/  t_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  UPRINTF (char*,char*) ; 
 int code ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_type (char*) ; 
 int /*<<< orphan*/  ttyout ; 
 char* typename ; 
 struct types* types ; 

void
settype(int argc, char *argv[])
{
	struct types *p;

	if (argc == 0 || argc > 2) {
		const char *sep;

		UPRINTF("usage: %s [", argv[0]);
		sep = " ";
		for (p = types; p->t_name; p++) {
			fprintf(ttyout, "%s%s", sep, p->t_name);
			sep = " | ";
		}
		fputs(" ]\n", ttyout);
		code = -1;
		return;
	}
	if (argc < 2) {
		fprintf(ttyout, "Using %s mode to transfer files.\n", typename);
		code = 0;
		return;
	}
	set_type(argv[1]);
}