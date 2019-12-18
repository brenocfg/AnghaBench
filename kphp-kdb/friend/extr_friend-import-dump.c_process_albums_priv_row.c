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
 scalar_t__ PK_album ; 
 int /*<<< orphan*/  adj_rec ; 
 size_t al_id ; 
 size_t al_owner_id ; 
 size_t al_type ; 
 size_t al_user_id ; 
 int conv_uid (scalar_t__) ; 
 int /*<<< orphan*/  output_conv_privacy (scalar_t__,scalar_t__,char*) ; 
 scalar_t__ user_id ; 

void process_albums_priv_row (void) {
  user_id = I[al_owner_id];
  int uid = conv_uid (user_id);

  if (uid < 0 || user_id <= 0 || user_id != I[al_user_id] || I[al_id] <= 0) {
    return;
  }

  output_conv_privacy (PK_album+I[al_id], I[al_type], "*G*A*0*A/A");

  adj_rec++;
}