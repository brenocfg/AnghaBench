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
struct ngm_connect {int /*<<< orphan*/  peerhook; int /*<<< orphan*/  ourhook; int /*<<< orphan*/  path; } ;
typedef  int /*<<< orphan*/  con ;

/* Variables and functions */
 int CMDRTN_ERROR ; 
 int CMDRTN_OK ; 
 int CMDRTN_USAGE ; 
 int /*<<< orphan*/  NGM_CONNECT ; 
 int /*<<< orphan*/  NGM_GENERIC_COOKIE ; 
 scalar_t__ NgSendMsg (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ngm_connect*,int) ; 
 int /*<<< orphan*/  csock ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static int
ConnectCmd(int ac, char **av)
{
	struct ngm_connect con;
	const char *path = ".";

	/* Get arguments */
	switch (ac) {
	case 5:
		path = av[1];
		ac--;
		av++;
		/* FALLTHROUGH */
	case 4:
		snprintf(con.path, sizeof(con.path), "%s", av[1]);
		snprintf(con.ourhook, sizeof(con.ourhook), "%s", av[2]);
		snprintf(con.peerhook, sizeof(con.peerhook), "%s", av[3]);
		break;
	default:
		return (CMDRTN_USAGE);
	}

	/* Send message */
	if (NgSendMsg(csock, path, NGM_GENERIC_COOKIE,
	    NGM_CONNECT, &con, sizeof(con)) < 0) {
		warn("send msg");
		return (CMDRTN_ERROR);
	}
	return (CMDRTN_OK);
}