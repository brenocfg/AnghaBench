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
 int CMDRTN_ERROR ; 
 int CMDRTN_OK ; 
 int CMDRTN_USAGE ; 
 int /*<<< orphan*/  NGM_GENERIC_COOKIE ; 
 int /*<<< orphan*/  NGM_SHUTDOWN ; 
 scalar_t__ NgSendMsg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csock ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static int
ShutdownCmd(int ac, char **av)
{
	char *path;

	/* Get arguments */
	switch (ac) {
	case 2:
		path = av[1];
		break;
	default:
		return (CMDRTN_USAGE);
	}

	/* Shutdown node */
	if (NgSendMsg(csock, path, NGM_GENERIC_COOKIE,
	    NGM_SHUTDOWN, NULL, 0) < 0) {
		warn("shutdown");
		return (CMDRTN_ERROR);
	}
	return (CMDRTN_OK);
}