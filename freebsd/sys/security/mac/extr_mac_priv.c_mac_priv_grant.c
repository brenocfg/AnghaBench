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
 int /*<<< orphan*/  MAC_GRANT_PROBE2 (int /*<<< orphan*/ ,int,struct ucred*,int) ; 
 int /*<<< orphan*/  MAC_POLICY_GRANT_NOSLEEP (int /*<<< orphan*/ ,struct ucred*,int) ; 
 int /*<<< orphan*/  priv_grant ; 

int
mac_priv_grant(struct ucred *cred, int priv)
{
	int error;

	MAC_POLICY_GRANT_NOSLEEP(priv_grant, cred, priv);
	MAC_GRANT_PROBE2(priv_grant, error, cred, priv);

	return (error);
}