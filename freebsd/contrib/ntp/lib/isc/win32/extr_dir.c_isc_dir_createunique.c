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
typedef  int /*<<< orphan*/  isc_result_t ;

/* Variables and functions */
 scalar_t__ EEXIST ; 
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 int chmod (char*,int) ; 
 scalar_t__ errno ; 
 int getpid () ; 
 int /*<<< orphan*/  isc__errno2result (scalar_t__) ; 
 scalar_t__ isdigit (char) ; 
 int mkdir (char*) ; 
 int strlen (char*) ; 

isc_result_t
isc_dir_createunique(char *templet) {
	isc_result_t result;
	char *x;
	char *p;
	int i;
	int pid;

	REQUIRE(templet != NULL);

	/*
	 * mkdtemp is not portable, so this emulates it.
	 */

	pid = getpid();

	/*
	 * Replace trailing Xs with the process-id, zero-filled.
	 */
	for (x = templet + strlen(templet) - 1; *x == 'X' && x >= templet;
	     x--, pid /= 10)
		*x = pid % 10 + '0';

	x++;			/* Set x to start of ex-Xs. */

	do {
		i = mkdir(templet);
		i = chmod(templet, 0700);

		if (i == 0 || errno != EEXIST)
			break;

		/*
		 * The BSD algorithm.
		 */
		p = x;
		while (*p != '\0') {
			if (isdigit(*p & 0xff))
				*p = 'a';
			else if (*p != 'z')
				++*p;
			else {
				/*
				 * Reset character and move to next.
				 */
				*p++ = 'a';
				continue;
			}

			break;
		}

		if (*p == '\0') {
			/*
			 * Tried all combinations.  errno should already
			 * be EEXIST, but ensure it is anyway for
			 * isc__errno2result().
			 */
			errno = EEXIST;
			break;
		}
	} while (1);

	if (i == -1)
		result = isc__errno2result(errno);
	else
		result = ISC_R_SUCCESS;

	return (result);
}