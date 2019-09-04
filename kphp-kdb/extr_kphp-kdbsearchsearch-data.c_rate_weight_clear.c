#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int p; } ;
struct TYPE_3__ {int p; } ;

/* Variables and functions */
 TYPE_2__ QRP ; 
 TYPE_1__ QRT ; 
 scalar_t__ query_rate_weights ; 

__attribute__((used)) static void rate_weight_clear (void) {
  query_rate_weights = 0;
  QRT.p = -1;
  QRP.p = -1;
}