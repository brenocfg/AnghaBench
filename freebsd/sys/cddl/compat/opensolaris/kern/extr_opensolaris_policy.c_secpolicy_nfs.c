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
typedef  int /*<<< orphan*/  cred_t ;

/* Variables and functions */
 int /*<<< orphan*/  PRIV_NFS_DAEMON ; 
 int priv_check_cred (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
secpolicy_nfs(cred_t *cr)
{

	return (priv_check_cred(cr, PRIV_NFS_DAEMON));
}