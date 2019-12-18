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
struct mac_lomac {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_LOMAC_TYPE_HIGH ; 
 int /*<<< orphan*/  MAC_LOMAC_TYPE_LOW ; 
 struct mac_lomac* SLOT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lomac_set_range (struct mac_lomac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lomac_set_single (struct mac_lomac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lomac_cred_create_init(struct ucred *cred)
{
	struct mac_lomac *dest;

	dest = SLOT(cred->cr_label);

	lomac_set_single(dest, MAC_LOMAC_TYPE_HIGH, 0);
	lomac_set_range(dest, MAC_LOMAC_TYPE_LOW, 0, MAC_LOMAC_TYPE_HIGH, 0);
}