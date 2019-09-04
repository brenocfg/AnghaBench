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
struct TYPE_2__ {int cur_idx; } ;

/* Variables and functions */
 TYPE_1__ garbage_collector ; 
 int lrand48 () ; 
 int uri_hash_prime ; 

void cache_garbage_collector_init (void) {
  garbage_collector.cur_idx = lrand48 () % uri_hash_prime;
}