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
 scalar_t__* I ; 
 int /*<<< orphan*/  PK_gifts ; 
 int /*<<< orphan*/ * S ; 
 int /*<<< orphan*/  adj_rec ; 
 int conv_uid (scalar_t__) ; 
 size_t me_key ; 
 size_t me_member_id ; 
 size_t me_value ; 
 int /*<<< orphan*/  output_conv_privacy (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ user_id ; 

void process_members_prefs_row (void) {
  user_id = I[me_member_id];
  int uid = conv_uid (user_id);

  if (uid < 0 || user_id <= 0 || strcmp (S[me_key], "giftsVisible")) {
    return;
  }

  output_conv_privacy (PK_gifts, I[me_value], "*G*A*0/A");

  adj_rec++;
}