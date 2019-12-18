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
 int /*<<< orphan*/  enact_scenarios () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int setugid (int) ; 
 int /*<<< orphan*/  stderr ; 

int
main(int argc, char *argv[])
{
	int error;

	fprintf(stderr, "test capabilities: ");
#ifdef SETSUGID_SUPPORTED
	fprintf(stderr, "[SETSUGID_SUPPORTED] ");
#endif
#ifdef SETSUGID_SUPPORTED_BUT_NO_LIBC_STUB
	fprintf(stderr, "[SETSUGID_SUPPORTED_BUT_NO_LIBC_STUB] ");
#endif
#ifdef CHECK_CRED_SET
	fprintf(stderr, "[CHECK_CRED_SET] ");
#endif
	fprintf(stderr, "\n");

	error = setugid(1);
	if (error) {
		perror("setugid");
		fprintf(stderr,
		    "This test suite requires options REGRESSION\n");
		return (-1);
	}

	enact_scenarios();

	return (0);
}