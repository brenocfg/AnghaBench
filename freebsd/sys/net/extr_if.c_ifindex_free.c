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
typedef  int /*<<< orphan*/  u_short ;

/* Variables and functions */
 int /*<<< orphan*/  IFNET_WLOCK () ; 
 int /*<<< orphan*/  IFNET_WUNLOCK () ; 
 int /*<<< orphan*/  ifindex_free_locked (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ifindex_free(u_short idx)
{

	IFNET_WLOCK();
	ifindex_free_locked(idx);
	IFNET_WUNLOCK();
}