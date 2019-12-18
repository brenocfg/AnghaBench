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
typedef  int ssize_t ;
typedef  int /*<<< orphan*/ * efidp ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int MAXSIZE ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int efidp_parse_device_path (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  stdin ; 
 char* trim (char*) ; 
 int /*<<< orphan*/  write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
parse(void)
{
	char buffer[MAXSIZE];
	efidp dp;
	ssize_t dplen;
	char *walker;

	dplen = MAXSIZE;
	dp = malloc(dplen);
	if (dp == NULL)
		errx(1, "Can't allocate memory.");
	while (fgets(buffer, sizeof(buffer), stdin)) {
		walker= trim(buffer);
		dplen = efidp_parse_device_path(walker, dp, dplen);
		if (dplen == -1)
			errx(1, "Can't parse %s", walker);
		write(STDOUT_FILENO, dp, dplen);
	}
	free(dp);
}