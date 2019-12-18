#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  dl_treap ;

/* Variables and functions */
 int /*<<< orphan*/  dl_trp_add (int /*<<< orphan*/ *,int,int) ; 
 int dl_trp_del (int /*<<< orphan*/ *,int) ; 
 int my_rand () ; 

void dl_trp_incr (dl_treap *tr, int x) {
  int y = dl_trp_del (tr, x);
  dl_trp_add (tr, x, (~(~((y) >> 16) + 1) << 16) | (my_rand() & 0xFFFF));
}