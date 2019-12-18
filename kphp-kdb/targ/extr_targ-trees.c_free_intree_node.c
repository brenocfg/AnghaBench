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
typedef  int /*<<< orphan*/  treeref_t ;
struct TYPE_4__ {int free_queue_cnt; int /*<<< orphan*/ * free_queue; } ;
struct TYPE_3__ {int /*<<< orphan*/  left; } ;

/* Variables and functions */
 TYPE_2__* TS_HEADER ; 
 TYPE_1__* TS_NODE (int /*<<< orphan*/ ) ; 
 int lrand48 () ; 

inline void free_intree_node (treespace_t TS, treeref_t N) {
  int q = lrand48() & (TS_HEADER->free_queue_cnt - 1);
  TS_NODE(N)->left = TS_HEADER->free_queue[q*2];
  TS_HEADER->free_queue[q*2] = N;
  TS_HEADER->free_queue[q*2+1]++;
}