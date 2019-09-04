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
struct lev_cache_set_local_copy_yellow_light_short {int /*<<< orphan*/  yellow_light_duration; int /*<<< orphan*/  packed_location; scalar_t__ data; } ;
struct cache_uri {int dummy; } ;
struct cache_local_copy {int /*<<< orphan*/  location; int /*<<< orphan*/  packed_location; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  md5_t ;
typedef  int /*<<< orphan*/  L ;

/* Variables and functions */
 int /*<<< orphan*/  CACHE_LOCAL_COPY_FLAG_INT ; 
 int /*<<< orphan*/  assert (struct cache_uri*) ; 
 struct cache_uri* cache_get_uri_by_md5 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cache_local_copy_unpack_location (struct cache_uri*,struct cache_local_copy*) ; 
 int cache_set_local_copy_yellow_light (struct cache_uri*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct cache_local_copy*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cache_set_local_copy_yellow_light_short (struct lev_cache_set_local_copy_yellow_light_short *E) {
  struct cache_uri *U = cache_get_uri_by_md5 ((md5_t *) E->data, 8);
  assert (U);
  struct cache_local_copy L;
  memset (&L, 0, sizeof (L));
  L.flags |= CACHE_LOCAL_COPY_FLAG_INT;
  L.packed_location = E->packed_location;
  cache_local_copy_unpack_location (U, &L);
  return cache_set_local_copy_yellow_light (U, L.location, E->yellow_light_duration);
}