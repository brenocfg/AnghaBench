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
 int /*<<< orphan*/  MAXPATHLEN ; 
 int /*<<< orphan*/  errno ; 
 char* getcwd (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror_r (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

char *
getwd(char *buf)
{
	char *p;

	if ( (p = getcwd(buf, MAXPATHLEN)) )
		return(p);
	(void)strerror_r(errno, buf, MAXPATHLEN);
	return((char *)NULL);
}