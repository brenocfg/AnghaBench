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
struct lev_pmemcached_incr {int /*<<< orphan*/  arg; int /*<<< orphan*/  key_len; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  cache_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pmemcached_incr_current (int /*<<< orphan*/ ) ; 

int pmemcached_incr (struct lev_pmemcached_incr *E) {
  cache_load (E->key, E->key_len, 0);
  return pmemcached_incr_current (E->arg);
}