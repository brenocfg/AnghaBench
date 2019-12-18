#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int local_id; struct TYPE_6__* hnext; TYPE_1__* B; } ;
typedef  TYPE_2__ metafile_t ;
struct TYPE_5__ {long long volume_id; } ;

/* Variables and functions */
 int HASH_META_PRIME ; 
 TYPE_2__** M ; 
 int /*<<< orphan*/  assert (int) ; 
 int get_meta_hash (long long,int) ; 

__attribute__((used)) static metafile_t *get_meta_f (long long volume_id, int local_id, int *h, int force) {
  *h = get_meta_hash (volume_id, local_id);
  assert ((*h) >= 0 && (*h) < HASH_META_PRIME);
  metafile_t **p = M + (*h), *V;
  while (*p) {
    V = *p;
    if (V->B->volume_id == volume_id && V->local_id == local_id) {
      *p = V->hnext;
      if (force >= 0) {
        V->hnext = M[*h];
        M[*h] = V;
      }
      return V;
    }
    p = &V->hnext;
  }
  return NULL;
}