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
typedef  TYPE_1__* change_list_ptr ;
struct TYPE_5__ {int /*<<< orphan*/ * next; scalar_t__ timestamp; int /*<<< orphan*/ * s; scalar_t__ x; scalar_t__ type; } ;

/* Variables and functions */
 TYPE_1__* chg_list_get_entry () ; 

void chg_list_init (change_list_ptr *st, change_list_ptr *en) {
  change_list_ptr v = chg_list_get_entry();
  v->type = 0;
  v->x = 0;
  v->s = NULL;
  v->timestamp = 0;
  v->next = NULL;
  *st = *en = v;
}