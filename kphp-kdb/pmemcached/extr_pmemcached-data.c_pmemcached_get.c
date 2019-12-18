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
struct lev_pmemcached_get {int /*<<< orphan*/  key_len; int /*<<< orphan*/  key; } ;
struct data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cache_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct data pmemcached_get_current () ; 

struct data pmemcached_get (struct lev_pmemcached_get *E) {
  cache_load (E->key, E->key_len, 0);
  return pmemcached_get_current ();
}