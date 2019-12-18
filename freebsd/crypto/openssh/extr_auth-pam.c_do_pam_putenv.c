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
 int /*<<< orphan*/  free (char*) ; 
 int pam_putenv (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*,char*) ; 
 int /*<<< orphan*/  sshpam_handle ; 
 int strlen (char*) ; 
 char* xmalloc (size_t) ; 

int
do_pam_putenv(char *name, char *value)
{
	int ret = 1;
#ifdef HAVE_PAM_PUTENV
	char *compound;
	size_t len;

	len = strlen(name) + strlen(value) + 2;
	compound = xmalloc(len);

	snprintf(compound, len, "%s=%s", name, value);
	ret = pam_putenv(sshpam_handle, compound);
	free(compound);
#endif

	return (ret);
}