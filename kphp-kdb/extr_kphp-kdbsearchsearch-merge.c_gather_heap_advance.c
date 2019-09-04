#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int cur; int remaining; scalar_t__ last; int value; int x; TYPE_3__* cur_chunk; } ;
typedef  TYPE_1__ gh_entry_t ;
struct TYPE_6__ {scalar_t__ data; struct TYPE_6__* next; } ;

/* Variables and functions */
 int CHUNK_INTS ; 
 TYPE_1__** GH ; 
 int GH_N ; 
 int GH_mode ; 
 int /*<<< orphan*/  assert (TYPE_3__*) ; 
 int g_double ; 
 int /*<<< orphan*/  load_heap_v (TYPE_1__*) ; 

__attribute__((used)) static void gather_heap_advance (void) {
  gh_entry_t *H;
  int sz = (GH_mode & g_double ? 3 : 2);
  if (!GH_N) { return; }
  H = GH[1];
  H->cur += sz;
  if (!--H->remaining) {
    H = GH[GH_N--];
    if (!GH_N) { return; }
  } else {
    if (H->cur >= H->last) {
      H->cur_chunk = H->cur_chunk->next;
      assert (H->cur_chunk);
      H->cur = H->cur_chunk->data;
      int t = H->remaining * sz;
      if (t > CHUNK_INTS) { t = CHUNK_INTS; }
      H->last = H->cur + t;
    }
    load_heap_v (H);
  }
  int i = 1, j, v = H->value, vx = H->x;
  while (1) {
    j = i*2;
    if (j > GH_N) { break; }
    if (j < GH_N && (GH[j+1]->value < GH[j]->value || (GH[j+1]->value == GH[j]->value && GH[j+1]->x < GH[j]->x))) { j++; }
    if (v < GH[j]->value || (v == GH[j]->value && vx <= GH[j]->x)) { break; }
    GH[i] = GH[j];
    i = j;
  }
  GH[i] = H;
}