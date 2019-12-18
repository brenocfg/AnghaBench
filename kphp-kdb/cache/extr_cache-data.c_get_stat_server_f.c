#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int id; struct TYPE_5__* hnext; } ;
typedef  TYPE_1__ cache_stat_server_t ;

/* Variables and functions */
 TYPE_1__** HSS ; 
 int STAT_SERVER_HASH_PRIME ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  tot_servers ; 
 TYPE_1__* zmalloc0 (int const) ; 

cache_stat_server_t *get_stat_server_f (int id, int force) {
  int h = id % STAT_SERVER_HASH_PRIME;
  assert (h >= 0 && h < STAT_SERVER_HASH_PRIME);
  cache_stat_server_t **p = HSS + h, *V;
  while (*p) {
    V = *p;
    if (id == V->id) {
      *p = V->hnext;
      if (force >= 0) {
        V->hnext = HSS[h];
        HSS[h] = V;
      }
      return V;
    }
    p = &V->hnext;
  }
  if (force > 0) {
    tot_servers++;
    const int sz = sizeof (cache_stat_server_t);
    V = zmalloc0 (sz);
    V->id = id;
    V->hnext = HSS[h];
    return HSS[h] = V;
  }
  return NULL;
}