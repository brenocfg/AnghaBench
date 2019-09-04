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
 scalar_t__* Friends ; 
 int MAX_USERS ; 
 int /*<<< orphan*/  output_user_friends (scalar_t__,scalar_t__) ; 
 int split_mod ; 
 scalar_t__ split_rem ; 

void output_all_friends (void) {
  int i;
  for (i = 0; i < MAX_USERS; i++) {
    if (Friends[i]) {
      output_user_friends (i*split_mod + split_rem, Friends[i]);
    }
  }
}