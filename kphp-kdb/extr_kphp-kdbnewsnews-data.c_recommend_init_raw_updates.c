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

/* Variables and functions */
 int PLACES_HASH ; 
 int RECOMMEND_PLACES_HASH ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ tot_places ; 

void recommend_init_raw_updates (void) {
  assert (tot_places == 0);
  assert (2 * RECOMMEND_PLACES_HASH <= PLACES_HASH);
}