#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  conv_uid (int) ; 
 int delete_user_by_idx (int /*<<< orphan*/ ) ; 
 scalar_t__ min_logevent_time ; 
 scalar_t__ now ; 

__attribute__((used)) static int delete_user (int user_id) {
  if (now < min_logevent_time) {
    return 0;
  }
  return delete_user_by_idx (conv_uid (user_id));
}