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
struct news_id {int dummy; } ;
struct gather_entry {scalar_t__ num; int res_read; int res_bytes; scalar_t__ data; } ;
struct TYPE_5__ {int remaining; struct news_id id; scalar_t__ last; scalar_t__ cur; } ;
typedef  TYPE_1__ gh_entry_t ;

/* Variables and functions */
 TYPE_1__** GH ; 
 TYPE_1__* GH_E ; 
 size_t GH_N ; 
 int GH_total ; 
 size_t MAX_CLUSTER_SERVERS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  load_heap_v (TYPE_1__*) ; 
 scalar_t__ news_id_compare (struct news_id,struct news_id) ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 

__attribute__((used)) static int gather_heap_insert (struct gather_entry *GE) {
  int cnt, cnt2, sz;
  gh_entry_t *H;
  assert (GH_N < MAX_CLUSTER_SERVERS);
  if (GE->num <= 0 || GE->res_read < 8 || !GE->data) {
    return 0;
  }
  cnt2 = cnt = (GE->res_read >> 2);
  sz = 6;
  cnt /= sz;
  cnt2 = cnt * sz;
  if (verbosity >= 3) {
    fprintf (stderr, "gather_heap_insert: %d elements (size %d)\n", cnt, (GE->res_read >> 2) - 1);
  }
  if (cnt <= 0) { 
    return 0;
  }
  GH_total += cnt;

  H = &GH_E[GH_N];
  H->remaining = cnt;
  H->cur = GE->data;
  H->last = GE->data + GE->res_bytes / 4 + 1;
  load_heap_v (H);

  int i = ++GH_N, j;
  struct news_id id = H->id;
  while (i > 1) {
    j = (i >> 1);
    if (news_id_compare (GH[j]->id, id) <= 0) { break; }
    GH[i] = GH[j];
    i = j;
  }
  GH[i] = H;

  return 1;
}