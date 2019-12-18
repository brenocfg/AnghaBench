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
 char* _PATH_MAILDIR ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 

void
findmail(char *user, char *buf, int buflen)
{
	char *tmp = getenv("MAIL");

	if (tmp == NULL)
		(void)snprintf(buf, buflen, "%s/%s", _PATH_MAILDIR, user);
	else
		(void)strlcpy(buf, tmp, buflen);
}