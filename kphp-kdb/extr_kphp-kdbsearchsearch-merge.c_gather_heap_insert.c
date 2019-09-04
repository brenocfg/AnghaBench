#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct gather_entry {scalar_t__ num; int res_read; TYPE_1__* first; } ;
struct TYPE_7__ {int remaining; int cur; int last; int value; int x; TYPE_1__* cur_chunk; } ;
typedef  TYPE_2__ gh_entry_t ;
struct TYPE_6__ {int data; } ;

/* Variables and functions */
 int CHUNK_INTS ; 
 TYPE_2__** GH ; 
 TYPE_2__* GH_E ; 
 size_t GH_N ; 
 int GH_mode ; 
 int GH_total ; 
 size_t MAX_CLUSTER_SERVERS ; 
 int /*<<< orphan*/  assert (int) ; 
 int g_double ; 
 int /*<<< orphan*/  load_heap_v (TYPE_2__*) ; 

__attribute__((used)) static int gather_heap_insert (struct gather_entry *GE) {
  int cnt, cnt2, sz;
  gh_entry_t *H;
  assert (GH_N < MAX_CLUSTER_SERVERS);
  if (GE->num <= 0 || GE->res_read < 8 || !GE->first) {
    return 0;
  }
  cnt2 = cnt = (GE->res_read >> 2) - 1;
  sz = (GH_mode & g_double) ? 3 : 2;
  cnt /= sz;
  cnt2 = cnt * sz;
  if (cnt <= 0) {
    return 0;
  }
  GH_total += cnt;

  H = &GH_E[GH_N];
  H->remaining = cnt;
  H->cur_chunk = GE->first;
  H->cur = H->cur_chunk->data;
  H->last = H->cur + (cnt2 < CHUNK_INTS ? cnt2 : CHUNK_INTS);
  load_heap_v (H);

  int v = H->value, vx = H->x, i = ++GH_N, j;
  while (i > 1) {
    j = (i >> 1);
    if (GH[j]->value < v || (GH[j]->value == v && GH[j]->x <= vx)) { break; }
    GH[i] = GH[j];
    i = j;
  }
  GH[i] = H;

  return 1;
}