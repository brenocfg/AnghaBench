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
 double M_LN2 ; 
 int /*<<< orphan*/ * Volumes ; 
 double exp (double) ; 
 int now ; 
 int /*<<< orphan*/  volume_relax_astat (int /*<<< orphan*/ ,double) ; 
 int volumes ; 

__attribute__((used)) static void volumes_relax_astat (void) {
  static int last_call_time = 0;
  double e = last_call_time ? exp ((-M_LN2 / 86400.0) * (now - last_call_time)) : 0.0;
  int i;
  for (i = 0; i < volumes; i++) {
    volume_relax_astat (Volumes[i], e);
  }
  last_call_time = now;
}