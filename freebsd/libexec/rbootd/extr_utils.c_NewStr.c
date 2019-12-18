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
 int /*<<< orphan*/  LOG_ERR ; 
 scalar_t__ malloc (unsigned int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,char*) ; 

char *
NewStr(char *str)
{
	char *stmp;

	if ((stmp = (char *)malloc((unsigned) (strlen(str)+1))) == NULL) {
		syslog(LOG_ERR, "NewStr: out of memory (%s)", str);
		return(NULL);
	}

	(void) strcpy(stmp, str);
	return(stmp);
}