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
struct label {int dummy; } ;

/* Variables and functions */
 scalar_t__ SLOT (struct label*) ; 
 int /*<<< orphan*/  SLOT_SET (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
partition_cred_relabel(struct ucred *cred, struct label *newlabel)
{

	if (newlabel != NULL && SLOT(newlabel) != 0)
		SLOT_SET(cred->cr_label, SLOT(newlabel));
}