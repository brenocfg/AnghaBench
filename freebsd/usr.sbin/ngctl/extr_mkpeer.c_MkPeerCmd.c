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
struct ngm_mkpeer {int /*<<< orphan*/  peerhook; int /*<<< orphan*/  ourhook; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  mkp ;

/* Variables and functions */
 int CMDRTN_ERROR ; 
 int CMDRTN_OK ; 
 int CMDRTN_USAGE ; 
 int /*<<< orphan*/  NGM_GENERIC_COOKIE ; 
 int /*<<< orphan*/  NGM_MKPEER ; 
 scalar_t__ NgSendMsg (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ngm_mkpeer*,int) ; 
 int /*<<< orphan*/  csock ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static int
MkPeerCmd(int ac, char **av)
{
	struct ngm_mkpeer mkp;
	const char *path = ".";

	/* Get arguments */
	switch (ac) {
	case 5:
		path = av[1];
		ac--;
		av++;
		/* FALLTHROUGH */
	case 4:
		snprintf(mkp.type, sizeof(mkp.type), "%s", av[1]);
		snprintf(mkp.ourhook, sizeof(mkp.ourhook), "%s", av[2]);
		snprintf(mkp.peerhook, sizeof(mkp.peerhook), "%s", av[3]);
		break;
	default:
		return (CMDRTN_USAGE);
	}

	/* Send message */
	if (NgSendMsg(csock, path, NGM_GENERIC_COOKIE,
	    NGM_MKPEER, &mkp, sizeof(mkp)) < 0) {
		warn("send msg");
		return (CMDRTN_ERROR);
	}
	return (CMDRTN_OK);
}