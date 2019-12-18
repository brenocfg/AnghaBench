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
struct ucred {int /*<<< orphan*/ * cr_label; } ;

/* Variables and functions */
 int MPC_OBJECT_CRED ; 
 int /*<<< orphan*/ * mac_cred_label_alloc () ; 
 int mac_labeled ; 

void
mac_cred_init(struct ucred *cred)
{

	if (mac_labeled & MPC_OBJECT_CRED)
		cred->cr_label = mac_cred_label_alloc();
	else
		cred->cr_label = NULL;
}