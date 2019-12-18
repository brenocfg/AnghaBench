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
struct ncpaddr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  alive; int /*<<< orphan*/  dial; int /*<<< orphan*/  out; int /*<<< orphan*/  in; } ;
struct bundle {TYPE_1__ filter; } ;

/* Variables and functions */
 int /*<<< orphan*/  filter_AdjustAddr (int /*<<< orphan*/ *,struct ncpaddr*,struct ncpaddr*,int /*<<< orphan*/ *) ; 

void
bundle_AdjustFilters(struct bundle *bundle, struct ncpaddr *local,
                     struct ncpaddr *remote)
{
  filter_AdjustAddr(&bundle->filter.in, local, remote, NULL);
  filter_AdjustAddr(&bundle->filter.out, local, remote, NULL);
  filter_AdjustAddr(&bundle->filter.dial, local, remote, NULL);
  filter_AdjustAddr(&bundle->filter.alive, local, remote, NULL);
}