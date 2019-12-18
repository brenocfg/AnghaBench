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
struct TYPE_2__ {int* dist_cache; } ;
struct rar5 {TYPE_1__ cstate; } ;

/* Variables and functions */

__attribute__((used)) static void dist_cache_push(struct rar5* rar, int value) {
	int* q = rar->cstate.dist_cache;

	q[3] = q[2];
	q[2] = q[1];
	q[1] = q[0];
	q[0] = value;
}