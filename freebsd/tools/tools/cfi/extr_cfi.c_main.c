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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 char* dvname ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 char* getenv (char*) ; 
 scalar_t__ getfactorypr () ; 
 scalar_t__ getoempr () ; 
 int getplr () ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 char* progname ; 
 int /*<<< orphan*/  setoempr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setplr () ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ strtoull (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{
	dvname = getenv("CFI");
	if (dvname == NULL)
		dvname = "/dev/cfi0";
	progname = argv[0];
	if (argc > 1) {
		if (strcmp(argv[1], "-f") == 0) {
			if (argc < 2)
				errx(1, "missing device name for -f option");
			dvname = argv[2];
			argc -= 2, argv += 2;
		} else if (strcmp(argv[1], "-?") == 0)
			usage();
	}
	for (; argc > 1; argc--, argv++) {
		if (strcasecmp(argv[1], "fact") == 0) {
			printf("0x%llx\n", (unsigned long long) getfactorypr());
		} else if (strcasecmp(argv[1], "oem") == 0) {
			printf("0x%llx\n", (unsigned long long) getoempr());
		} else if (strcasecmp(argv[1], "woem") == 0) {
			if (argc < 2)
				errx(1, "missing value for woem");
			setoempr((uint64_t) strtoull(argv[2], NULL, 0));
			argc--, argv++;
		} else if (strcasecmp(argv[1], "plr") == 0) {
			printf("0x%x\n", getplr());
		} else if (strcasecmp(argv[1], "wplr") == 0) {
			setplr();
		} else
			usage();
	}
}