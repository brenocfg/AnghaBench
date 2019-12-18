#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* next_used; TYPE_1__* prev_used; } ;
typedef  TYPE_3__ user ;
struct TYPE_6__ {TYPE_1__* prev_used; } ;
struct TYPE_5__ {TYPE_2__* next_used; } ;

/* Variables and functions */

void del_user_used (user *u) {
  u->next_used->prev_used = u->prev_used;
  u->prev_used->next_used = u->next_used;
}