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
struct ucred {int dummy; } ;
struct pipepair {int /*<<< orphan*/  pp_label; int /*<<< orphan*/  pp_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_CHECK_PROBE4 (int /*<<< orphan*/ ,int,struct ucred*,struct pipepair*,unsigned long,void*) ; 
 int /*<<< orphan*/  MAC_POLICY_CHECK_NOSLEEP (int /*<<< orphan*/ ,struct ucred*,struct pipepair*,int /*<<< orphan*/ ,unsigned long,void*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pipe_check_ioctl ; 

int
mac_pipe_check_ioctl(struct ucred *cred, struct pipepair *pp,
    unsigned long cmd, void *data)
{
	int error;

	mtx_assert(&pp->pp_mtx, MA_OWNED);

	MAC_POLICY_CHECK_NOSLEEP(pipe_check_ioctl, cred, pp, pp->pp_label,
	    cmd, data);
	MAC_CHECK_PROBE4(pipe_check_ioctl, error, cred, pp, cmd, data);

	return (error);
}