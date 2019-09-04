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
struct data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pmemcached_check_time_current () ; 
 struct data pmemcached_get_current () ; 

struct data do_pmemcached_get (const char *key, int key_len) {
#ifdef LOG_PMEMCACHED_GET
  //long long hash = get_hash (key, key_len);
  struct lev_pmemcached_get *E = alloc_log_event(LEV_PMEMCACHED_GET, offsetof(struct lev_pmemcached_get,key)+1+key_len, 0);
  E->key_len = key_len;
  //E->hash = hash;
  memcpy (E->key, key, key_len);
  E->key[key_len] = 0;
  return pmemcached_get (E);
#else
  //return pmemcached_get_common (key, key_len, hash);
  pmemcached_check_time_current ();
  return pmemcached_get_current ();
#endif
}