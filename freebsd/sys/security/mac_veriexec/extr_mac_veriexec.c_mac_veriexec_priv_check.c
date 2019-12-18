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

/* Variables and functions */
 int EPERM ; 
#define  PRIV_KMEM_WRITE 128 
 int VERIEXEC_STATE_ENFORCE ; 
 int /*<<< orphan*/  curproc ; 
 int /*<<< orphan*/  mac_veriexec_proc_is_trusted (struct ucred*,int /*<<< orphan*/ ) ; 
 int mac_veriexec_state ; 

__attribute__((used)) static int
mac_veriexec_priv_check(struct ucred *cred, int priv)
{

	/* If we are not enforcing veriexec, nothing for us to check */
	if ((mac_veriexec_state & VERIEXEC_STATE_ENFORCE) == 0)
		return (0);

	switch (priv) {
	case PRIV_KMEM_WRITE:
		if (!mac_veriexec_proc_is_trusted(cred, curproc))
			return (EPERM);
		break;
	default:
		break;
	}
	return (0);
}