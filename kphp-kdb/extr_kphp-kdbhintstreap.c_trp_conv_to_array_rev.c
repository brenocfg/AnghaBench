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
struct TYPE_3__ {int size; int /*<<< orphan*/  root; } ;
typedef  TYPE_1__ treap ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int trp_dfs (int /*<<< orphan*/ ,int*) ; 

int trp_conv_to_array_rev (treap tr, int *res) {
  assert (trp_dfs (tr.root, res) == -tr.size);
  return -tr.size;
}