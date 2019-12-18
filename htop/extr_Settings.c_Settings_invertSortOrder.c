#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int direction; } ;
typedef  TYPE_1__ Settings ;

/* Variables and functions */

void Settings_invertSortOrder(Settings* this) {
   if (this->direction == 1)
      this->direction = -1;
   else
      this->direction = 1;
}