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
typedef  long long uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  LBUF ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fgets (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* lbuf ; 
 int /*<<< orphan*/  printf (char*,char const*,...) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 int strlen (char*) ; 

__attribute__((used)) static int
decimal(const char *str, int *num, int deflt, uint32_t maxval)
{
	long long acc;
	int c;
	char *cp;

	while (1) {
		acc = 0;
		printf("Supply a decimal value for \"%s\" [%d] ", str, deflt);
		fflush(stdout);
		if (fgets(lbuf, LBUF, stdin) == NULL)
			exit(1);
		lbuf[strlen(lbuf)-1] = 0;

		if (!*lbuf)
			return 0;

		cp = lbuf;
		while ((c = *cp) && (c == ' ' || c == '\t')) cp++;
		if (!c)
			return 0;
		while ((c = *cp++)) {
			if (c <= '9' && c >= '0') {
				if (acc <= maxval || maxval == 0)
					acc = acc * 10 + c - '0';
			} else
				break;
		}
		if (c == ' ' || c == '\t')
			while ((c = *cp) && (c == ' ' || c == '\t')) cp++;
		if (!c) {
			if (maxval > 0 && acc > maxval) {
				acc = maxval;
				printf("%s exceeds maximum value allowed for "
				  "this field. The value has been reduced "
				  "to %lld\n", lbuf, acc);
			}
			*num = acc;
			return 1;
		} else
			printf("%s is an invalid decimal number.  Try again.\n",
				lbuf);
	}
}