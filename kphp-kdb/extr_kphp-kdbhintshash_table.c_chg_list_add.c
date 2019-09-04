#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* change_list_ptr ;
struct TYPE_6__ {int type; int x; struct TYPE_6__* next; int /*<<< orphan*/  number; int /*<<< orphan*/  timestamp; } ;

/* Variables and functions */
 TYPE_1__* chg_list_get_entry () ; 
 int /*<<< orphan*/  now ; 

inline change_list_ptr chg_list_add (change_list_ptr *st, change_list_ptr *en, int type, int x) {
  static int autoincrement = 0;

  change_list_ptr v = chg_list_get_entry();
  v->type = type;
  v->x = x;
  v->timestamp = now;
  v->number = autoincrement++;

  v->next = NULL;
  if (*st == NULL) {
    *st = v;
  } else {
    (*en)->next = v;
  }
  *en = v;

  return v;
}