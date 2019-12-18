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
struct futx {int fu_type; int /*<<< orphan*/  fu_id; } ;
typedef  int /*<<< orphan*/  off_t ;
typedef  int /*<<< orphan*/  fe ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int ESRCH ; 
#define  INIT_PROCESS 130 
#define  LOGIN_PROCESS 129 
 int /*<<< orphan*/  SEEK_CUR ; 
#define  USER_PROCESS 128 
 int /*<<< orphan*/  _PATH_UTX_ACTIVE ; 
 int errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int fread (struct futx*,int,int,int /*<<< orphan*/ *) ; 
 int fseeko (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * futx_open (int /*<<< orphan*/ ) ; 
 int fwrite (struct futx*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
utx_active_remove(struct futx *fu)
{
	FILE *fp;
	struct futx fe;
	int error, ret;

	/*
	 * Remove user login sessions, having the same ut_id.
	 */
	fp = futx_open(_PATH_UTX_ACTIVE);
	if (fp == NULL)
		return (-1);
	error = ESRCH;
	ret = -1;
	while (fread(&fe, sizeof(fe), 1, fp) == 1 && ret != 0)
		switch (fe.fu_type) {
		case USER_PROCESS:
		case INIT_PROCESS:
		case LOGIN_PROCESS:
			if (memcmp(fu->fu_id, fe.fu_id, sizeof(fe.fu_id)) != 0)
				continue;

			/* Terminate session. */
			if (fseeko(fp, -(off_t)sizeof(fe), SEEK_CUR) == -1)
				error = errno;
			else if (fwrite(fu, sizeof(*fu), 1, fp) < 1)
				error = errno;
			else
				ret = 0;

		}

	fclose(fp);
	if (ret != 0)
		errno = error;
	return (ret);
}