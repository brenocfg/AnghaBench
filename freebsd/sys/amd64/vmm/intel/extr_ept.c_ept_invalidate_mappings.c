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
typedef  int /*<<< orphan*/  u_long ;
struct invept_desc {int /*<<< orphan*/  eptp; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  invept_single_context ; 
 int /*<<< orphan*/  smp_rendezvous (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct invept_desc*) ; 

void
ept_invalidate_mappings(u_long eptp)
{
	struct invept_desc invept_desc = { 0 };

	invept_desc.eptp = eptp;

	smp_rendezvous(NULL, invept_single_context, NULL, &invept_desc);
}