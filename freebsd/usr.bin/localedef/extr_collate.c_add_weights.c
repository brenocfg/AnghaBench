#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int NUM_WT ; 
 int /*<<< orphan*/  add_weight (int /*<<< orphan*/ ,int) ; 

void
add_weights(int32_t *refs)
{
	int i;
	for (i = 0; i < NUM_WT; i++) {
		add_weight(refs[i], i);
	}
}