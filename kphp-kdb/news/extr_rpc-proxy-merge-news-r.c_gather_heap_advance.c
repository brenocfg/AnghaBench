#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct news_id {int dummy; } ;
struct TYPE_4__ {int cur; scalar_t__ last; struct news_id id; int /*<<< orphan*/  remaining; } ;
typedef  TYPE_1__ gh_entry_t ;

/* Variables and functions */
 TYPE_1__** GH ; 
 int GH_N ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_heap_v (TYPE_1__*) ; 
 scalar_t__ news_id_compare (struct news_id,struct news_id) ; 

__attribute__((used)) static void gather_heap_advance (void) {
  gh_entry_t *H;
  int sz = 6;
  if (!GH_N) { return; }
  H = GH[1];
  H->cur += sz;
  if (!--H->remaining) {
    H = GH[GH_N--];
    if (!GH_N) { return; }
  } else {
    if (H->cur >= H->last) {
      assert (0);
    }
    load_heap_v (H);
  }
  int i = 1, j;
  struct news_id id = H->id;
  while (1) {
    j = i*2;
    if (j > GH_N) { break; }
    if (j < GH_N && news_id_compare (GH[j + 1]->id, GH[j]->id) < 0) {j ++; }
    if (news_id_compare (id, GH[j]->id) <= 0) { break; }
    GH[i] = GH[j];
    i = j;
  }
  GH[i] = H;
}