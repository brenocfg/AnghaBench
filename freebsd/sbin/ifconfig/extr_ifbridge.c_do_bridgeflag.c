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
struct ifbreq {int ifbr_ifsflags; int /*<<< orphan*/  ifbr_ifsname; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  BRDGGIFFLGS ; 
 int /*<<< orphan*/  BRDGSIFFLGS ; 
 scalar_t__ do_cmd (int,int /*<<< orphan*/ ,struct ifbreq*,int,int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static void
do_bridgeflag(int sock, const char *ifs, int flag, int set)
{
	struct ifbreq req;

	strlcpy(req.ifbr_ifsname, ifs, sizeof(req.ifbr_ifsname));

	if (do_cmd(sock, BRDGGIFFLGS, &req, sizeof(req), 0) < 0)
		err(1, "unable to get bridge flags");

	if (set)
		req.ifbr_ifsflags |= flag;
	else
		req.ifbr_ifsflags &= ~flag;

	if (do_cmd(sock, BRDGSIFFLGS, &req, sizeof(req), 1) < 0)
		err(1, "unable to set bridge flags");
}