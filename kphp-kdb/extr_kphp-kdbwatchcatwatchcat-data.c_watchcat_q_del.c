#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {struct TYPE_8__* next; TYPE_2__* parent; TYPE_1__* prev; } ;
typedef  TYPE_3__ watchcat ;
struct TYPE_7__ {int /*<<< orphan*/  vn; } ;
struct TYPE_6__ {TYPE_3__* next; } ;

/* Variables and functions */

inline watchcat *watchcat_q_del (watchcat *e) {
  e->next->prev = e->prev;
  e->prev->next = e->next;

  e->parent->vn--;

  return e->next;
}