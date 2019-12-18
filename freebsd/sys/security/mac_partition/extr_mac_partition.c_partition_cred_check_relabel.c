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
struct label {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PRIV_MAC_PARTITION ; 
 scalar_t__ SLOT (struct label*) ; 
 int priv_check_cred (struct ucred*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
partition_cred_check_relabel(struct ucred *cred, struct label *newlabel)
{
	int error;

	error = 0;

	/*
	 * Treat "0" as a no-op request because it reflects an unset
	 * partition label.  If we ever want to support switching back to an
	 * unpartitioned state for a process, we'll need to differentiate the
	 * "not in a partition" and "no partition defined during internalize"
	 * conditions.
	 */
	if (SLOT(newlabel) != 0) {
		/*
		 * Require BSD privilege in order to change the partition.
		 * Originally we also required that the process not be in a
		 * partition in the first place, but this didn't interact
		 * well with sendmail.
		 */
		error = priv_check_cred(cred, PRIV_MAC_PARTITION);
	}

	return (error);
}