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
 int PRIME ; 
 scalar_t__* UserModHeaders ; 
 int /*<<< orphan*/  dyn_purge_deleted_user_messages (scalar_t__) ; 

void dyn_purge_all_deleted_messages (void) {
  int i;
  for (i = 0; i < PRIME; i++) {
    if (UserModHeaders[i]) {
      dyn_purge_deleted_user_messages(UserModHeaders[i]);
    }
  }
}