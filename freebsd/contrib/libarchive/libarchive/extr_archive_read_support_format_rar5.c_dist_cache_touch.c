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

__attribute__((used)) static int dist_cache_touch(struct rar5* rar, int idx) {
	int* q = rar->cstate.dist_cache;
	int i, dist = q[idx];

	for(i = idx; i > 0; i--)
		q[i] = q[i - 1];

	q[0] = dist;
	return dist;
}