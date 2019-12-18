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
struct TYPE_2__ {scalar_t__ difference; } ;
typedef  TYPE_1__ doublesorthelper ;

/* Variables and functions */

__attribute__((used)) static int comparedoublesorthelper(const void * ina, const void * inb) {
        doublesorthelper * a = (doublesorthelper * )ina;
        doublesorthelper * b = (doublesorthelper * )inb;
        if (a->difference > b->difference) {
                return 1;
        } else if (a->difference == b->difference) {
                return 0;
        } else {
                return -1;
        }
}