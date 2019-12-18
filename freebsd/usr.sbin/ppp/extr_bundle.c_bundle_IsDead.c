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
struct bundle {scalar_t__ phase; scalar_t__ CleaningUp; int /*<<< orphan*/  links; } ;

/* Variables and functions */
 scalar_t__ PHASE_DEAD ; 

int
bundle_IsDead(struct bundle *bundle)
{
  return !bundle->links || (bundle->phase == PHASE_DEAD && bundle->CleaningUp);
}