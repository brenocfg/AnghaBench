#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  enum rounding { ____Placeholder_rounding } rounding ;
struct TYPE_4__ {int round; } ;
typedef  TYPE_1__ decContext ;

/* Variables and functions */

decContext *decContextSetRounding(decContext *context,
                                  enum rounding newround) {
  context->round=newround;
  return context;
  }