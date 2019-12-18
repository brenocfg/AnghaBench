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
typedef  int /*<<< orphan*/  rating ;
typedef  int /*<<< orphan*/  change_list_ptr ;
struct TYPE_2__ {int /*<<< orphan*/  val; } ;

/* Variables and functions */
 TYPE_1__* chg_list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  write_only ; 

void chg_list_add_rating (change_list_ptr *st, change_list_ptr *en, int type, int x, rating val) {
  if (!write_only) {
    chg_list_add (st, en, type, x)->val = val;
  }
}