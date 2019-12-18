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
struct TYPE_5__ {int /*<<< orphan*/  prm; } ;
typedef  TYPE_1__ data ;

/* Variables and functions */
 int PERM (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int data_move (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  data_restore_fix (TYPE_1__*,int,int,int) ; 
 int /*<<< orphan*/  get_i ; 

int data_move_new (data *d, int i, int j, int local_i, int local_j) {
  if (1) {
    int prev_i = i == 0 ? -1 : PERM (get_i, &d->prm, i - 1);
    assert (prev_i >= -1);
    data_restore_fix (d, prev_i, local_i, local_j);
  }

  return data_move (d, i, j);
}