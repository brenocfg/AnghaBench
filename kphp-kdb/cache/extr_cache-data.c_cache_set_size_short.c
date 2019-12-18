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
struct lev_cache_set_size_short {int /*<<< orphan*/  size; scalar_t__ data; } ;
struct cache_uri {int dummy; } ;
typedef  int /*<<< orphan*/  md5_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (struct cache_uri*) ; 
 struct cache_uri* cache_get_uri_by_md5 (int /*<<< orphan*/ *,int) ; 
 struct cache_uri* cache_set_size (struct cache_uri*,int /*<<< orphan*/ ) ; 

void cache_set_size_short (struct lev_cache_set_size_short *E) {
  struct cache_uri *U = cache_get_uri_by_md5 ((md5_t *) E->data, 8);
  assert (U);
  U = cache_set_size (U, E->size);
}