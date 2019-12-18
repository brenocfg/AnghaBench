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
struct TYPE_3__ {int rate; } ;
typedef  TYPE_1__ user_t ;

/* Variables and functions */
 TYPE_1__* get_user (int) ; 

int get_user_rate (int user_id) {
  user_t *U = get_user (user_id);
  return U ? U->rate : (-1 << 31);
}