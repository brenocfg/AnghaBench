#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int prev_used; int next_bucket; } ;

/* Variables and functions */
 int MAX_BUFF ; 
 int STAT_ST ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  black_list_check (scalar_t__) ; 
 scalar_t__ buff ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,int) ; 
 scalar_t__* names ; 
 scalar_t__ names_buff ; 
 TYPE_1__* q_entry ; 
 int* q_rev ; 
 int qr ; 
 int /*<<< orphan*/  stderr ; 

int *get_top_v (int need) {
  int *v = (int *)buff;
  v[0] = 0;
  int t = q_entry[0].prev_used;

  int ignore_black_list = 0;
  if (need < 0) {
    need = -need;
    ignore_black_list = 1;
  }
  if (need > 10000) {
    need = 10000;
  }
  if (need < 0) {
    need = 0;
  }

  assert ((need + 1) * sizeof (int) < MAX_BUFF);
  while (t && need) {
    int st = t, curr = t;

    assert (0 <= curr && curr < qr);
    assert (q_entry[curr].next_bucket != st);

    while (q_entry[curr].next_bucket != st && need) {
      if (!(0 <= curr && curr < STAT_ST + qr)) {
        fprintf (stderr, "%d < %d < %d\n", 0, curr, STAT_ST + qr);
        assert (0 <= curr && curr < STAT_ST + qr);
      }

      curr = q_entry[curr].next_bucket;

      if (!(STAT_ST <= curr && curr < qr + STAT_ST)) {
        fprintf (stderr, "%d < %d < %d\n", STAT_ST, curr, qr + STAT_ST);
        assert (STAT_ST <= curr && curr < qr + STAT_ST);
      }

      v[++v[0]] = q_rev[curr - STAT_ST];
      if (ignore_black_list || !black_list_check (names_buff + names[v[v[0]]])) {
        need--;
      } else {
        v[0]--;
      }
    }
    t = q_entry[t].prev_used;
  }
  return v;
}