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
typedef  int treeref_t ;
struct TYPE_4__ {int free_queue_cnt; int* free_queue; } ;
struct TYPE_3__ {int left; } ;

/* Variables and functions */
 TYPE_2__* TS_HEADER ; 
 TYPE_1__* TS_NODE (int) ; 
 int /*<<< orphan*/  alloc_new_intree_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int lrand48 () ; 

treeref_t new_intree_node (treespace_t TS) {
  // XA-XA 5 PA3
  int m = TS_HEADER->free_queue_cnt - 1;
  long q = lrand48() & m;
  int p = TS_HEADER->free_queue[q*2];
  if (!p) {
    int i = 5;
    while (--i) {
      q = lrand48() & m;
      p = TS_HEADER->free_queue[q*2];
      if (p) {
        break;
      }
    }
    if (!p) {
      assert (!TS_HEADER->free_queue[q*2+1]);
      alloc_new_intree_page (TS);
      p = TS_HEADER->free_queue[q*2];
      assert (p);
    }
  }
  TS_HEADER->free_queue[q*2] = TS_NODE(p)->left;
  assert (--TS_HEADER->free_queue[q*2+1] >= 0);
  return p;
}