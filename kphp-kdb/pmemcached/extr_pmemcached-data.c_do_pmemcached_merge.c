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
 int /*<<< orphan*/  assert (int) ; 
 int cache_load (char const*,int,int) ; 

void do_pmemcached_merge (const char *key, int key_len) {
  assert(cache_load (key, key_len, 1) != -2);
  //return current_cache->hash_entry;
}