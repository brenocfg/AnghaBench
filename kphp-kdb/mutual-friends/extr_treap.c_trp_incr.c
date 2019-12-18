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
typedef  int /*<<< orphan*/  treap ;

/* Variables and functions */
 int my_rand () ; 
 int /*<<< orphan*/  trp_add (int /*<<< orphan*/ *,int,int) ; 
 int trp_del (int /*<<< orphan*/ *,int) ; 

void trp_incr (treap *tr, int x, int add) {
  int y = trp_del (tr, x);
  trp_add (tr, x, (y  + (add << 16)) ^ (my_rand() & 0xFFFF));
}