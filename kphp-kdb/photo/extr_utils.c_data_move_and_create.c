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
struct TYPE_3__ {int /*<<< orphan*/  prm; } ;
typedef  TYPE_1__ data ;

/* Variables and functions */
 int PERM (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  move_and_create ; 

int data_move_and_create (data *d, int i, int j) {
//  dbg ("move and create %d %d\n", i, j);
  return PERM (move_and_create, &d->prm, i, j);
}