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
struct pipepair {int /*<<< orphan*/  pp_mtx; } ;
struct label {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int mac_pipe_check_relabel (struct ucred*,struct pipepair*,struct label*) ; 
 int /*<<< orphan*/  mac_pipe_relabel (struct ucred*,struct pipepair*,struct label*) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
mac_pipe_label_set(struct ucred *cred, struct pipepair *pp,
    struct label *label)
{
	int error;

	mtx_assert(&pp->pp_mtx, MA_OWNED);

	error = mac_pipe_check_relabel(cred, pp, label);
	if (error)
		return (error);

	mac_pipe_relabel(cred, pp, label);

	return (0);
}