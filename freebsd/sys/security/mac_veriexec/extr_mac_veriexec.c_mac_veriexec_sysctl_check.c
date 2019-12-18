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
struct sysctl_req {int dummy; } ;
struct sysctl_oid {int oid_kind; } ;

/* Variables and functions */
 int CTLFLAG_SECURE ; 
 int EPERM ; 
 int VERIEXEC_STATE_ENFORCE ; 
 int mac_veriexec_state ; 

__attribute__((used)) static int
mac_veriexec_sysctl_check(struct ucred *cred, struct sysctl_oid *oidp,
    void *arg1, int arg2, struct sysctl_req *req)
{
	struct sysctl_oid *oid;

	/* If we are not enforcing veriexec, nothing for us to check */
	if ((mac_veriexec_state & VERIEXEC_STATE_ENFORCE) == 0)
		return (0);

	oid = oidp;
	if (oid->oid_kind & CTLFLAG_SECURE) {
		return (EPERM);		/* XXX call mac_veriexec_priv_check? */
	}
	return 0;
}