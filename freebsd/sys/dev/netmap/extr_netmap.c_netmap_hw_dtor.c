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
struct netmap_adapter {int /*<<< orphan*/ * ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  NM_DETACH_NA (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
netmap_hw_dtor(struct netmap_adapter *na)
{
	if (na->ifp == NULL)
		return;

	NM_DETACH_NA(na->ifp);
}