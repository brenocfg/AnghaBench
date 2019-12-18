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
struct modes {int /*<<< orphan*/ * m_name; int /*<<< orphan*/  m_mode; } ;

/* Variables and functions */
 char* mode ; 
 struct modes* modes ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  settftpmode (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
modecmd(int argc, char *argv[])
{
	struct modes *p;
	const char *sep;

	if (argc < 2) {
		printf("Using %s mode to transfer files.\n", mode);
		return;
	}
	if (argc == 2) {
		for (p = modes; p->m_name; p++)
			if (strcmp(argv[1], p->m_name) == 0)
				break;
		if (p->m_name) {
			settftpmode(p->m_mode);
			return;
		}
		printf("%s: unknown mode\n", argv[1]);
		/* drop through and print usage message */
	}

	printf("usage: %s [", argv[0]);
	sep = " ";
	for (p = modes; p->m_name != NULL; p++) {
		printf("%s%s", sep, p->m_name);
		if (*sep == ' ')
			sep = " | ";
	}
	printf(" ]\n");
	return;
}