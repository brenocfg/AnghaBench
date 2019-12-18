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

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  lf_clearremotesys_iterator ; 
 int /*<<< orphan*/  lf_iteratelocks_sysid (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
lf_clearremotesys(int sysid)
{

	KASSERT(sysid != 0, ("Can't clear local locks with F_UNLCKSYS"));
	lf_iteratelocks_sysid(sysid, lf_clearremotesys_iterator, NULL);
}