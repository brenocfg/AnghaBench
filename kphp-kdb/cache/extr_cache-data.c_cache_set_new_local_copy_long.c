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
struct lev_cache_set_new_local_copy_long {int /*<<< orphan*/  data; scalar_t__ md5; } ;
struct cache_uri {int dummy; } ;
struct cache_local_copy {scalar_t__* location; } ;
typedef  int /*<<< orphan*/  md5_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 struct cache_uri* cache_get_uri_by_md5 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cache_local_copy_init (struct cache_local_copy*) ; 
 int /*<<< orphan*/  cache_local_copy_try_pack_location (struct cache_uri*,struct cache_local_copy*) ; 
 int cache_set_new_local_copy (struct cache_uri*,struct cache_local_copy*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cache_set_new_local_copy_long (struct lev_cache_set_new_local_copy_long *E, int local_url_len) {
  struct cache_uri *U = cache_get_uri_by_md5 ((md5_t *) E->md5, 16);
  assert (U);
  struct cache_local_copy L;
  cache_local_copy_init (&L);
  assert (local_url_len < sizeof (L.location));
  memcpy (L.location, E->data, local_url_len);
  L.location[local_url_len] = 0;
  cache_local_copy_try_pack_location (U, &L);
  return cache_set_new_local_copy (U, &L);
}