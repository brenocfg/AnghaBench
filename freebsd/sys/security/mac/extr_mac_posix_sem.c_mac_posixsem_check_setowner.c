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
typedef  int /*<<< orphan*/  uid_t ;
struct ucred {int dummy; } ;
struct ksem {int /*<<< orphan*/  ks_label; } ;
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_CHECK_PROBE4 (int /*<<< orphan*/ ,int,struct ucred*,struct ksem*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAC_POLICY_CHECK_NOSLEEP (int /*<<< orphan*/ ,struct ucred*,struct ksem*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  posixsem_check_setowner ; 

int
mac_posixsem_check_setowner(struct ucred *cred, struct ksem *ks, uid_t uid,
    gid_t gid)
{
	int error;

	MAC_POLICY_CHECK_NOSLEEP(posixsem_check_setowner, cred, ks,
	    ks->ks_label, uid, gid);
	MAC_CHECK_PROBE4(posixsem_check_setowner, error, cred, ks,
	    uid, gid);

	return (error);
}