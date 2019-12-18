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
struct ksem {int /*<<< orphan*/  ks_label; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_POLICY_PERFORM_NOSLEEP (int /*<<< orphan*/ ,struct ucred*,struct ksem*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  posixsem_create ; 

void
mac_posixsem_create(struct ucred *cred, struct ksem *ks)
{

	MAC_POLICY_PERFORM_NOSLEEP(posixsem_create, cred, ks, ks->ks_label);
}