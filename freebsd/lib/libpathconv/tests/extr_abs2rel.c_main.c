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
 int MAXPATHLEN ; 
 scalar_t__ abs2rel (char*,char*,char*,int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  getcwd (char*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

int
main(int argc, char *argv[])
{
	char result[MAXPATHLEN];
	char cwd[MAXPATHLEN];

	if (argc < 2) {
		fprintf(stderr, "usage: abs2rel path [base]\n");
		exit(1);
	}
	if (argc == 2) {
		if (!getcwd(cwd, MAXPATHLEN)) {
			fprintf(stderr, "cannot get current directory.\n");
			exit(1);
		}
	} else
		strcpy(cwd, argv[2]);
	
	if (abs2rel(argv[1], cwd, result, MAXPATHLEN)) {
		printf("%s\n", result);
	} else
		printf("ERROR\n");
	exit(0);
}