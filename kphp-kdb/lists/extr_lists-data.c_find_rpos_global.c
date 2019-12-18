#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int N; size_t* IA; scalar_t__* DA; } ;
typedef  TYPE_1__ listree_global_t ;
typedef  scalar_t__ global_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

int find_rpos_global (listree_global_t *LG, global_id_t global_id) {
  int l = -1, r = LG->N, x;

  /* A[j]:=DA[IA[j]] ; A[N-i-1]<x<=A[N-i] means A[l] < x <= A[r]; i = N - r */
  while (r - l > 1) {
    x = (l + r) / 2;
    if (global_id <= (global_id_t)LG->DA[LG->IA[x]]) {
      r = x;
    } else {
      l = x;
    }
  }
  assert (r >= 0 && r <= LG->N);
  return LG->N - r;
}