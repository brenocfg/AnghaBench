#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int user_cnt; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int GET_USER_INFO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_USER_INFO (int /*<<< orphan*/ ,int) ; 
 TYPE_2__ header ; 
 int /*<<< orphan*/  indexed_users ; 
 TYPE_1__* users ; 

void update_user_info (void) {
  int i;
  for (i = 1; i <= header.user_cnt; i++) {
    if (GET_USER_INFO (users[i].flags) != 1) {
      users[i].flags = SET_USER_INFO (users[i].flags, -1);
    } else {
      indexed_users++;
    }
  }
}