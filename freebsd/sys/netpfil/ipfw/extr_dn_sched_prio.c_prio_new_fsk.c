#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * par; } ;
struct dn_fsk {TYPE_1__ fs; } ;

/* Variables and functions */
 scalar_t__ MAXPRIO ; 
 int /*<<< orphan*/  ipdn_bound_var (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,char*) ; 

__attribute__((used)) static int
prio_new_fsk(struct dn_fsk *fs)
{
	/* Check if the prioritiy is between 0 and MAXPRIO-1 */
	ipdn_bound_var(&fs->fs.par[0], 0, 0, MAXPRIO - 1, "PRIO priority");
	return 0;
}