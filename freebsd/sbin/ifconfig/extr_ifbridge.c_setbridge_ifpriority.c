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
typedef  int u_long ;
struct ifbreq {int ifbr_priority; int /*<<< orphan*/  ifbr_ifsname; } ;
struct afswtch {int dummy; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  BRDGSIFPRIO ; 
 scalar_t__ do_cmd (int,int /*<<< orphan*/ ,struct ifbreq*,int,int) ; 
 int /*<<< orphan*/  err (int,char*,char const*) ; 
 int /*<<< orphan*/  errx (int,char*,char const*) ; 
 scalar_t__ get_val (char const*,int*) ; 
 int /*<<< orphan*/  memset (struct ifbreq*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static void
setbridge_ifpriority(const char *ifn, const char *pri, int s,
    const struct afswtch *afp)
{
	struct ifbreq req;
	u_long val;

	memset(&req, 0, sizeof(req));

	if (get_val(pri, &val) < 0 || (val & ~0xff) != 0)
		errx(1, "invalid value: %s",  pri);

	strlcpy(req.ifbr_ifsname, ifn, sizeof(req.ifbr_ifsname));
	req.ifbr_priority = val & 0xff;

	if (do_cmd(s, BRDGSIFPRIO, &req, sizeof(req), 1) < 0)
		err(1, "BRDGSIFPRIO %s",  pri);
}