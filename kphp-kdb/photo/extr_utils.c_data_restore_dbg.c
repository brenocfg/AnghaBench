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
typedef  int /*<<< orphan*/  restore_list ;
struct TYPE_3__ {int /*<<< orphan*/  restore_info; } ;
typedef  TYPE_1__ data ;

/* Variables and functions */
 int /*<<< orphan*/  dbg (char*,int,int /*<<< orphan*/ **) ; 
 scalar_t__ map_int_vptr_get (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  restore_list_dbg (int /*<<< orphan*/ *) ; 

void data_restore_dbg (data *d, int v) {
  restore_list **list = (restore_list **)map_int_vptr_get (&d->restore_info, v);
  dbg ("list %d: %p\n", v, list);
  if (list != NULL) {
    restore_list_dbg (*list);
  }
}