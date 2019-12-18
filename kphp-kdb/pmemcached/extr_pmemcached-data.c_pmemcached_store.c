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
struct lev_pmemcached_store {int type; int /*<<< orphan*/  delay; int /*<<< orphan*/  flags; int /*<<< orphan*/  data_len; scalar_t__ key_len; scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  cache_load (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int pmemcached_store_current (int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int pmemcached_store (struct lev_pmemcached_store *E) {
  cache_load (E->data, E->key_len, 0);
  return pmemcached_store_current (E->type & 3, E->data+E->key_len, E->data_len, E->flags, E->delay);
}