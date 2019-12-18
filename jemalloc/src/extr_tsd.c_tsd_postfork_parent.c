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
typedef  int /*<<< orphan*/  tsd_t ;

/* Variables and functions */
 int /*<<< orphan*/  malloc_mutex_postfork_parent (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsd_nominal_tsds_lock ; 
 int /*<<< orphan*/  tsd_tsdn (int /*<<< orphan*/ *) ; 

void
tsd_postfork_parent(tsd_t *tsd) {
	malloc_mutex_postfork_parent(tsd_tsdn(tsd), &tsd_nominal_tsds_lock);
}