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
struct ucred {int /*<<< orphan*/  cr_label; } ;
struct mac_mls {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_MLS_TYPE_HIGH ; 
 int /*<<< orphan*/  MAC_MLS_TYPE_LOW ; 
 struct mac_mls* SLOT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mls_set_effective (struct mac_mls*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mls_set_range (struct mac_mls*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mls_cred_create_init(struct ucred *cred)
{
	struct mac_mls *dest;

	dest = SLOT(cred->cr_label);

	mls_set_effective(dest, MAC_MLS_TYPE_LOW, 0, NULL);
	mls_set_range(dest, MAC_MLS_TYPE_LOW, 0, NULL, MAC_MLS_TYPE_HIGH, 0,
	    NULL);
}