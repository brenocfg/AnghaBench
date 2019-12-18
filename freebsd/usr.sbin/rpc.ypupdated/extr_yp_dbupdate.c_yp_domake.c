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
 int /*<<< orphan*/  MAP_UPDATE ; 
 int /*<<< orphan*/  MAP_UPDATE_PATH ; 
 int YPERR_YPERR ; 
 int /*<<< orphan*/  children ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  execlp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int fork () ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yp_error (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
yp_domake(char *map, char *domain)
{
	int pid;

	switch ((pid = fork())) {
	case 0:
		execlp(MAP_UPDATE_PATH, MAP_UPDATE, map, domain, (char *)NULL);
		yp_error("couldn't exec map update process: %s",
						strerror(errno));
		exit(1);
		break;
	case -1:
		yp_error("fork() failed: %s", strerror(errno));
		return(YPERR_YPERR);
		break;
	default:
		children++;
		break;
	}

	return(0);
}