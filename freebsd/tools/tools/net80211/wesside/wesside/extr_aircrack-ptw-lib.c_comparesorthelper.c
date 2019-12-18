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
struct TYPE_2__ {scalar_t__ distance; } ;
typedef  TYPE_1__ sorthelper ;

/* Variables and functions */

__attribute__((used)) static int comparesorthelper(const void * ina, const void * inb) {
	sorthelper * a = (sorthelper * ) ina;
	sorthelper * b = (sorthelper * ) inb;
	if (a->distance > b->distance) {
		return 1;
	} else if (a->distance == b->distance) {
		return 0;
	} else {
		return -1;
	}
}