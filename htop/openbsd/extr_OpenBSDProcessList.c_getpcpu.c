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
struct kinfo_proc {int /*<<< orphan*/  p_pctcpu; } ;

/* Variables and functions */
 scalar_t__ fscale ; 
 double fxtofl (int /*<<< orphan*/ ) ; 

double getpcpu(const struct kinfo_proc *kp) {
   if (fscale == 0)
      return (0.0);

#define   fxtofl(fixpt)   ((double)(fixpt) / fscale)

   return (100.0 * fxtofl(kp->p_pctcpu));
}