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
struct lev_del_privacy {scalar_t__ key; } ;
typedef  scalar_t__ privacy_key_t ;

/* Variables and functions */
 int /*<<< orphan*/  LEV_FR_DEL_PRIVACY ; 
 struct lev_del_privacy* alloc_log_event (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ conv_uid (int) ; 
 int delete_privacy (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  get_user (int) ; 

int do_delete_privacy (int user_id, privacy_key_t privacy_key) {
  if (conv_uid (user_id) < 0 || !privacy_key) {
    return -1;
  }

  struct lev_del_privacy *E = alloc_log_event (LEV_FR_DEL_PRIVACY, 16, user_id);
  E->key = privacy_key;

  return delete_privacy (get_user (user_id), privacy_key);
}