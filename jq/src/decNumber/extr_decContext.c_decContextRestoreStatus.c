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
typedef  int uInt ;
struct TYPE_4__ {int status; } ;
typedef  TYPE_1__ decContext ;

/* Variables and functions */

decContext *decContextRestoreStatus(decContext *context,
                                    uInt newstatus, uInt mask) {
  context->status&=~mask;               // clear the selected bits
  context->status|=(mask&newstatus);    // or in the new bits
  return context;
  }