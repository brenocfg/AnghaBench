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
struct TYPE_2__ {scalar_t__ votes; } ;
typedef  TYPE_1__ PTW_tableentry ;

/* Variables and functions */

__attribute__((used)) static int compare(const void * ina, const void * inb) {
        PTW_tableentry * a = (PTW_tableentry * )ina;
        PTW_tableentry * b = (PTW_tableentry * )inb;
        if (a->votes > b->votes) {
                return -1;
        } else if (a->votes == b->votes) {
                return 0;
        } else {
                return 1;
        }
}