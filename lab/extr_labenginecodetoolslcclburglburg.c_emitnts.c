#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int ern; struct TYPE_3__* link; int /*<<< orphan*/  pattern; } ;
typedef  TYPE_1__* Rule ;

/* Variables and functions */
 void* alloc (int) ; 
 scalar_t__* computents (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  print (char*,...) ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strcpy (void*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static void emitnts(Rule rules, int nrules) {
	Rule r;
	int i, j, *nts = alloc((nrules + 1)*sizeof *nts);
	char **str = alloc((nrules + 1)*sizeof *str);

	for (i = 0, r = rules; r; r = r->link) {
		char buf[1024];
		*computents(r->pattern, buf) = 0;
		for (j = 0; str[j] && strcmp(str[j], buf); j++)
			;
		if (str[j] == NULL) {
			print("static short %Pnts_%d[] = { %s0 };\n", j, buf);
			str[j] = strcpy(alloc(strlen(buf) + 1), buf);
		}
		nts[i++] = j;
	}
	print("\nstatic short *%Pnts[] = {\n");
	for (i = j = 0, r = rules; r; r = r->link) {
		for ( ; j < r->ern; j++)
			print("%10,%1/* %d */\n", j);
		print("%1%Pnts_%d,%1/* %d */\n", nts[i++], j++);
	}
	print("};\n\n");
}