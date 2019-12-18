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
struct TYPE_4__ {scalar_t__ time; } ;
typedef  TYPE_1__ lwKey ;

/* Variables and functions */

__attribute__((used)) static int compare_keys( lwKey *k1, lwKey *k2 ){
	return k1->time > k2->time ? 1 : k1->time < k2->time ? -1 : 0;
}