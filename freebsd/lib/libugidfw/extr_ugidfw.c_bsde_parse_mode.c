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
typedef  scalar_t__ mode_t ;

/* Variables and functions */
 scalar_t__ MBI_ADMIN ; 
 scalar_t__ MBI_EXEC ; 
 scalar_t__ MBI_READ ; 
 scalar_t__ MBI_STAT ; 
 scalar_t__ MBI_WRITE ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,...) ; 
 int strlen (char*) ; 

int
bsde_parse_mode(int argc, char *argv[], mode_t *mode, size_t buflen,
    char *errstr)
{
	int i;

	if (argc == 0) {
		snprintf(errstr, buflen, "mode expects mode value");
		return (-1);
	}

	if (argc != 1) {
		snprintf(errstr, buflen, "'%s' unexpected", argv[1]);
		return (-1);
	}

	*mode = 0;
	for (i = 0; i < strlen(argv[0]); i++) {
		switch (argv[0][i]) {
		case 'a':
			*mode |= MBI_ADMIN;
			break;
		case 'r':
			*mode |= MBI_READ;
			break;
		case 's':
			*mode |= MBI_STAT;
			break;
		case 'w':
			*mode |= MBI_WRITE;
			break;
		case 'x':
			*mode |= MBI_EXEC;
			break;
		case 'n':
			/* ignore */
			break;
		default:
			snprintf(errstr, buflen, "Unknown mode letter: %c",
			    argv[0][i]);
			return (-1);
		}
	}

	return (0);
}