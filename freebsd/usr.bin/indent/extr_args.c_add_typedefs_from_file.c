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
 int BUFSIZ ; 
 int /*<<< orphan*/  add_typename (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  stderr ; 
 size_t strcspn (char*,char*) ; 

void
add_typedefs_from_file(const char *str)
{
    FILE *file;
    char line[BUFSIZ];

    if ((file = fopen(str, "r")) == NULL) {
	fprintf(stderr, "indent: cannot open file %s\n", str);
	exit(1);
    }
    while ((fgets(line, BUFSIZ, file)) != NULL) {
	/* Remove trailing whitespace */
	line[strcspn(line, " \t\n\r")] = '\0';
	add_typename(line);
    }
    fclose(file);
}