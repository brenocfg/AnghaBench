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
struct TYPE_3__ {struct TYPE_3__* prev; struct TYPE_3__* next; } ;
typedef  TYPE_1__ olist_t ;

/* Variables and functions */

__attribute__((used)) static inline void online_list_clear (olist_t *head) {
  olist_t *tmp = head->next;
  while (tmp != head) {
    olist_t *tnext = tmp->next;
    tmp->next = tmp->prev = 0;
    tmp = tnext;
  }
  head->next = head->prev = head;
}