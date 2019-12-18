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
typedef  int /*<<< orphan*/  u_long ;
struct devreq {int dr_flags; int /*<<< orphan*/  dr_name; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int devctl_request (int /*<<< orphan*/ ,struct devreq*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  memset (struct devreq*,int /*<<< orphan*/ ,int) ; 
 int strlcpy (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static int
devctl_simple_request(u_long cmd, const char *name, int flags)
{
	struct devreq req;

	memset(&req, 0, sizeof(req));
	if (strlcpy(req.dr_name, name, sizeof(req.dr_name)) >=
	    sizeof(req.dr_name)) {
		errno = EINVAL;
		return (-1);
	}
	req.dr_flags = flags;
	return (devctl_request(cmd, &req));
}