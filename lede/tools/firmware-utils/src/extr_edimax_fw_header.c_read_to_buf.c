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
 int /*<<< orphan*/  ERRS (char*,char*) ; 
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fread (char*,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int read_to_buf(char *name, char *buf, int buflen)
{
	FILE *f;
	int ret = EXIT_FAILURE;

	f = fopen(name, "r");
	if (f == NULL) {
		ERRS("could not open \"%s\" for reading", name);
		goto out;
	}

	errno = 0;
	fread(buf, buflen, 1, f);
	if (errno != 0) {
		ERRS("unable to read from file \"%s\"", name);
		goto out_close;
	}

	ret = EXIT_SUCCESS;

out_close:
	fclose(f);
out:
	return ret;
}