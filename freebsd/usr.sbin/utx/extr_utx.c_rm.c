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
struct utmpx {int /*<<< orphan*/  ut_id; int /*<<< orphan*/  ut_tv; int /*<<< orphan*/  ut_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEAD_PROCESS ; 
 scalar_t__ b16_pton (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  gettimeofday (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/ * pututxline (struct utmpx*) ; 
 int /*<<< orphan*/  stderr ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
rm(char *id[])
{
	struct utmpx utx = { .ut_type = DEAD_PROCESS };
	size_t len;
	int ret = 0;

	(void)gettimeofday(&utx.ut_tv, NULL);
	for (; *id != NULL; id++) {
		len = strlen(*id);
		if (len <= sizeof(utx.ut_id)) {
			/* Identifier as string. */
			strncpy(utx.ut_id, *id, sizeof(utx.ut_id));
		} else if (len != sizeof(utx.ut_id) * 2 ||
		    b16_pton(*id, utx.ut_id, sizeof(utx.ut_id)) != 0) {
			/* Also not hexadecimal. */
			fprintf(stderr, "%s: Invalid identifier format\n", *id);
			ret = 1;
			continue;
		}

		/* Zap the entry. */
		if (pututxline(&utx) == NULL) {
			perror(*id);
			ret = 1;
		}
	}
	return (ret);
}