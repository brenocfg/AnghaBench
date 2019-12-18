#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* first; } ;
typedef  TYPE_1__ userplace_t ;
typedef  int /*<<< orphan*/  notify_user_t ;
struct TYPE_5__ {int item; int date; struct TYPE_5__* next; } ;
typedef  TYPE_2__ notify_t ;
typedef  int /*<<< orphan*/  notify_place_t ;

/* Variables and functions */
 scalar_t__ min_logevent_time ; 
 scalar_t__ now ; 

__attribute__((used)) static int show_hide_notify_userplace (userplace_t *up, notify_user_t *U, notify_place_t *V,  int item, int shown) {
  if (now < min_logevent_time) {
    return 0;
  }
  notify_t *p;
  int res = 0;
  for (p = up->first; p != (notify_t *) up; p = p->next) {
    if (p->item == item && (p->date ^ shown) >= 0) {
      res++;
      p->date ^= (-1 << 31);
    }
  }
  return res;
}