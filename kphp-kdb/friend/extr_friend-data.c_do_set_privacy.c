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
typedef  int /*<<< orphan*/  user_t ;
struct lev_set_privacy_long {int len; int /*<<< orphan*/  List; void* key; } ;
struct lev_set_privacy {int /*<<< orphan*/  List; void* key; } ;
typedef  void* privacy_key_t ;

/* Variables and functions */
 scalar_t__ LEV_FR_SET_PRIVACY ; 
 scalar_t__ LEV_FR_SET_PRIVACY_LONG ; 
 int /*<<< orphan*/  Q ; 
 int QL ; 
 void* alloc_log_event (scalar_t__,int,int) ; 
 scalar_t__ conv_uid (int) ; 
 int /*<<< orphan*/ * get_user (int) ; 
 int /*<<< orphan*/ * get_user_f (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pack_privacy () ; 
 scalar_t__ parse_prepare_privacy (char const*,int,int) ; 
 int set_privacy (int /*<<< orphan*/ *,void*,int) ; 

int do_set_privacy (int user_id, privacy_key_t privacy_key, const char *text, int len, int force) {
  user_t *U;

  if (conv_uid (user_id) < 0 || !privacy_key) {
    return -1;
  }

  if (parse_prepare_privacy (text, len, user_id) < 0) {
    return -1;
  }

  pack_privacy ();

  if (QL < 256) {
    struct lev_set_privacy *E = alloc_log_event (LEV_FR_SET_PRIVACY + QL + (force ? 0x100 : 0), 16+QL*4, user_id);
    E->key = privacy_key;
    memcpy (E->List, Q, QL*4);
  } else {
    struct lev_set_privacy_long *E = alloc_log_event (LEV_FR_SET_PRIVACY_LONG + (force ? 1 : 0), 20+QL*4, user_id);
    E->key = privacy_key;
    E->len = QL;
    memcpy (E->List, Q, QL*4);
  }

  if (!force) {
    U = get_user (user_id);
  } else {
    U = get_user_f (user_id);
  }

  return set_privacy (U, privacy_key, force);
}