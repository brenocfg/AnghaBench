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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ feof (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int getc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ignore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  onintr (int /*<<< orphan*/ ) ; 
 char* strings ; 
 int /*<<< orphan*/  warn (char*,char*) ; 

__attribute__((used)) static void
xsdotc(void)
{
	FILE *strf = fopen(strings, "r");
	FILE *xdotcf;

	if (strf == NULL)
		err(5, "%s", strings);
	xdotcf = fopen("xs.c", "w");
	if (xdotcf == NULL)
		err(6, "xs.c");
	fprintf(xdotcf, "char\txstr[] = {\n");
	for (;;) {
		int i, c;

		for (i = 0; i < 8; i++) {
			c = getc(strf);
			if (ferror(strf)) {
				warn("%s", strings);
				onintr(0);
			}
			if (feof(strf)) {
				fprintf(xdotcf, "\n");
				goto out;
			}
			fprintf(xdotcf, "0x%02x,", c);
		}
		fprintf(xdotcf, "\n");
	}
out:
	fprintf(xdotcf, "};\n");
	ignore(fclose(xdotcf));
	ignore(fclose(strf));
}