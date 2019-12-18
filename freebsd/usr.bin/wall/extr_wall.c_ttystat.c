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
typedef  int /*<<< orphan*/  ttybuf ;
struct stat {int dummy; } ;

/* Variables and functions */
 int MAXPATHLEN ; 
 char* _PATH_DEV ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 scalar_t__ stat (char*,struct stat*) ; 

__attribute__((used)) static int
ttystat(char *line)
{
	struct stat sb;
	char ttybuf[MAXPATHLEN];

	(void)snprintf(ttybuf, sizeof(ttybuf), "%s%s", _PATH_DEV, line);
	if (stat(ttybuf, &sb) == 0) {
		return (0);
	} else
		return (-1);
}