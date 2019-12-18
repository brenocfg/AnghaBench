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
struct TYPE_2__ {int done; } ;
struct bundle {TYPE_1__ idle; } ;

/* Variables and functions */
 int time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
bundle_RemainingIdleTime(struct bundle *bundle)
{
  if (bundle->idle.done)
    return bundle->idle.done - time(NULL);
  return -1;
}