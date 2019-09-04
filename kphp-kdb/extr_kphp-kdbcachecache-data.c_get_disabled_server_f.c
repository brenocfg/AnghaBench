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
struct cache_local_copy_server {int id; struct cache_local_copy_server* hnext; } ;

/* Variables and functions */
 int DISABLED_SERVER_HASH_PRIME ; 
 struct cache_local_copy_server** HDS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  tot_disabled_servers ; 
 struct cache_local_copy_server* zmalloc0 (int const) ; 

struct cache_local_copy_server *get_disabled_server_f (int id, int force) {
  int h = id % DISABLED_SERVER_HASH_PRIME;
  assert (h >= 0 && h < DISABLED_SERVER_HASH_PRIME);
  struct cache_local_copy_server **p = HDS + h, *V;
  while (*p) {
    V = *p;
    if (id == V->id) {
      *p = V->hnext;
      if (force >= 0) {
        V->hnext = HDS[h];
        HDS[h] = V;
      }
      return V;
    }
    p = &V->hnext;
  }
  if (force > 0) {
    tot_disabled_servers++;
    const int sz = sizeof (struct cache_local_copy_server);
    V = zmalloc0 (sz);
    V->id = id;
    V->hnext = HDS[h];
    return HDS[h] = V;
  }
  return NULL;
}