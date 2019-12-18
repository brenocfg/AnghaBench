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
 int cache_load (char const*,int,int) ; 

int do_pmemcached_preload (const char *key, int key_len, int forceload) {
  int x = cache_load (key, key_len, forceload);
/*  if (x != -2) {
    pmemcached_check_time_current ();
  }*/
  return x;
}