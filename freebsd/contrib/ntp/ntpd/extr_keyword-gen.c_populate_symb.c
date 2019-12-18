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
typedef  int /*<<< orphan*/  line ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int COUNTOF (int /*<<< orphan*/ *) ; 
 int MAX_TOK_LEN ; 
 int /*<<< orphan*/  estrdup (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,char*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int sscanf (char*,char*,char*,int*) ; 
 int /*<<< orphan*/  stderr ; 
 int strlen (char*) ; 
 int /*<<< orphan*/ * symb ; 

void
populate_symb(
	char *header_file
	)
{
	FILE *	yh;
	char	line[2 * MAX_TOK_LEN];
	char	name[2 * MAX_TOK_LEN];
	int	token;

	yh = fopen(header_file, "r");
	if (NULL == yh) {
		perror("unable to open yacc/bison header file");
		exit(4);
	}

	while (NULL != fgets(line, sizeof(line), yh))
		if (2 == sscanf(line, "#define %s %d", name, &token)
		    && 'T' == name[0] && '_' == name[1] && token >= 0
		    && token < COUNTOF(symb)) {

			symb[token] = estrdup(name);
			if (strlen(name) > MAX_TOK_LEN) {
				fprintf(stderr,
					"MAX_TOK_LEN %d too small for '%s'\n"
					"Edit keyword-gen.c to raise.\n",
					MAX_TOK_LEN, name);
				exit(10);
			}
		}
	fclose(yh);
}