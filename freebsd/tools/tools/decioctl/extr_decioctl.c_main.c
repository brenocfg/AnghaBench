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
 int IOCGROUP (unsigned long) ; 
 int /*<<< orphan*/  IOCPARM_LEN (unsigned long) ; 
 unsigned long IOC_DIRMASK ; 
#define  IOC_IN 131 
#define  IOC_INOUT 130 
#define  IOC_OUT 129 
#define  IOC_VOID 128 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ isprint (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 unsigned long strtoul (char*,char**,int /*<<< orphan*/ ) ; 
 char* sysdecode_ioctlname (unsigned long) ; 
 int /*<<< orphan*/  usage (char**) ; 

int
main(int ac, char **av)
{
	unsigned long cmd;
	const char *name;
	char *cp;
	int group, i;

	if (ac < 2)
		usage(av);
	printf("  command :  dir  group num  len name\n");
	for (i = 1; i < ac; i++) {
		errno = 0;
		cmd = strtoul(av[i], &cp, 0);
		if (*cp != '\0' || errno != 0) {
			fprintf(stderr, "Invalid integer: %s\n", av[i]);
			usage(av);
		}
		printf("0x%08lx: ", cmd);
		switch (cmd & IOC_DIRMASK) {
		case IOC_VOID:
			printf("VOID ");
			break;
		case IOC_OUT:
			printf("OUT  ");
			break;
		case IOC_IN:
			printf("IN   ");
			break;
		case IOC_INOUT:
			printf("INOUT");
			break;
		default:
			printf("%01lx ???", (cmd & IOC_DIRMASK) >> 29);
			break;
		}
		printf(" ");
		group = IOCGROUP(cmd);
		if (isprint(group))
			printf(" '%c' ", group);
		else
			printf(" 0x%02x", group);
		printf(" %3lu %4lu", cmd & 0xff, IOCPARM_LEN(cmd));
		name = sysdecode_ioctlname(cmd);
		if (name != NULL)
			printf(" %s", name);
		printf("\n");
	}
	return (0);
}