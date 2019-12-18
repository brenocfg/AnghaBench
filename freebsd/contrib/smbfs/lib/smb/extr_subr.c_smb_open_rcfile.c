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
 int ENOENT ; 
 int /*<<< orphan*/  SMB_CFG_FILE ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (char*) ; 
 char* malloc (scalar_t__) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int rc_merge (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int rc_open (char*,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * smb_rc ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 scalar_t__ strlen (char*) ; 

int
smb_open_rcfile(void)
{
	char *home, *fn;
	int error;

	home = getenv("HOME");
	if (home) {
		fn = malloc(strlen(home) + 20);
		sprintf(fn, "%s/.nsmbrc", home);
		error = rc_open(fn, "r", &smb_rc);
		free(fn);
	}
	error = rc_merge(SMB_CFG_FILE, &smb_rc);
	if (smb_rc == NULL) {
		printf("Warning: no cfg file(s) found.\n");
		return ENOENT;
	}
	return 0;
}