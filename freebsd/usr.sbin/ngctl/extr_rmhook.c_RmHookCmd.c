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
struct ngm_rmhook {int /*<<< orphan*/  ourhook; } ;
typedef  int /*<<< orphan*/  rmh ;

/* Variables and functions */
 int CMDRTN_ERROR ; 
 int CMDRTN_OK ; 
 int CMDRTN_USAGE ; 
 int /*<<< orphan*/  NGM_GENERIC_COOKIE ; 
 int /*<<< orphan*/  NGM_RMHOOK ; 
 scalar_t__ NgSendMsg (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ngm_rmhook*,int) ; 
 int /*<<< orphan*/  csock ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static int
RmHookCmd(int ac, char **av)
{
	struct ngm_rmhook rmh;
	const char *path = ".";

	/* Get arguments */
	switch (ac) {
	case 3:
		path = av[1];
		ac--;
		av++;
		/* FALLTHROUGH */
	case 2:
		snprintf(rmh.ourhook, sizeof(rmh.ourhook), "%s", av[1]);
		break;
	default:
		return (CMDRTN_USAGE);
	}

	/* Send message */
	if (NgSendMsg(csock, path, NGM_GENERIC_COOKIE,
	    NGM_RMHOOK, &rmh, sizeof(rmh)) < 0) {
		warn("send msg");
		return (CMDRTN_ERROR);
	}
	return (CMDRTN_OK);
}