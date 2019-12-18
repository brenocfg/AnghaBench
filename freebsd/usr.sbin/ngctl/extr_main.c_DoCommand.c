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
struct ngcmd {int (* func ) (int,char**) ;int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 int CMDRTN_ERROR ; 
 int CMDRTN_OK ; 
 int CMDRTN_USAGE ; 
 struct ngcmd* FindCommand (char*) ; 
 int stub1 (int,char**) ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
DoCommand(int ac, char **av)
{
	const struct ngcmd *cmd;
	int rtn;

	if (ac == 0 || *av[0] == 0)
		return (CMDRTN_OK);
	if ((cmd = FindCommand(av[0])) == NULL)
		return (CMDRTN_ERROR);
	if ((rtn = (*cmd->func)(ac, av)) == CMDRTN_USAGE)
		warnx("usage: %s", cmd->cmd);
	return (rtn);
}