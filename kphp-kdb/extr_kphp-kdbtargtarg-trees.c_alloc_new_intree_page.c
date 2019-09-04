#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  treespace_t ;
struct TYPE_4__ {unsigned int used_ints; unsigned int free_queue_cnt; unsigned int node_ints; unsigned int alloc_ints; unsigned int* free_queue; } ;
struct TYPE_3__ {unsigned int left; } ;

/* Variables and functions */
 TYPE_2__* TS_HEADER ; 
 TYPE_1__* TS_NODE (unsigned int) ; 
 int /*<<< orphan*/  assert (int) ; 

inline void alloc_new_intree_page (treespace_t TS) {
  unsigned s = TS_HEADER->used_ints;
  unsigned N = TS_HEADER->free_queue_cnt;
  unsigned sz = TS_HEADER->node_ints;
  assert (s + N*sz <= TS_HEADER->alloc_ints);
#if 0
  int *A = TS + s + (sz - 1)*N;
  int i, j;
  for (i = 0; i < N; i++) {
    j = lrand48() % (i + 1);
    A[i] = A[j];
    A[j] = i;
  }
  for (i = 0; i < N; i++, s += sz) {
    int q = A[i];
#else
  int q;
  for (q = 0; q < N; q++, s += sz) {
#endif
    TS_NODE(s)->left = TS_HEADER->free_queue[q*2];
    TS_HEADER->free_queue[q*2] = s;
    TS_HEADER->free_queue[q*2+1]++;
  }
  TS_HEADER->used_ints = s;
}