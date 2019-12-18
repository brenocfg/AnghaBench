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
struct auth_rrset {struct auth_rrset* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct auth_rrset*) ; 

__attribute__((used)) static void
auth_rrset_delete(struct auth_rrset* rrset)
{
	if(!rrset) return;
	free(rrset->data);
	free(rrset);
}