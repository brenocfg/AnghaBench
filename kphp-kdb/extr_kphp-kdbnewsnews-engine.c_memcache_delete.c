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
struct connection {int /*<<< orphan*/  Out; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMM_MODE ; 
 int /*<<< orphan*/  C_INTIMEOUT ; 
 int /*<<< orphan*/  NOTIFY_MODE ; 
 int /*<<< orphan*/  UG_MODE ; 
 int /*<<< orphan*/  delete_queries ; 
 int do_add_del_bookmark (int,int,int,int,int /*<<< orphan*/ ) ; 
 int do_delete_comment (int,int,int,int) ; 
 int do_delete_place (int,int,int) ; 
 int do_delete_user (int) ; 
 int do_delete_user_comment (int,int,int,int,int) ; 
 int do_undelete_comment (int,int,int,int) ; 
 int do_undelete_user_comment (int,int,int,int,int) ; 
 int sscanf (char const*,char*,int*,...) ; 
 int ug_mode ; 
 int /*<<< orphan*/  undelete_queries ; 
 int /*<<< orphan*/  write_out (int /*<<< orphan*/ *,char*,int) ; 

int memcache_delete (struct connection *c, const char *key, int key_len) {
  c->flags &= ~C_INTIMEOUT;
  int user_id, type, owner, place, item, res = 0;
  switch (*key) {
  case 'u':
    if (UG_MODE && sscanf (key, "updates%d", &user_id) == 1 && user_id && (user_id ^ ug_mode) >= 0) {
      delete_queries++;
      res = do_delete_user (user_id);
    } else if (COMM_MODE && sscanf (key, "undelete_comm_update%d_%d_%d_%d", &type, &owner, &place, &item) == 4 && place > 0 && item > 0) {
      undelete_queries++;
      res = do_undelete_comment (type, owner, place, item);
    } else if (NOTIFY_MODE && sscanf (key, "undelete_notification_update%d_%d_%d_%d", &type, &owner, &place, &item) == 4 && place > 0 && item >= 0) {
      undelete_queries++;
      res = do_undelete_comment (type, owner, place, item);
    } else if (NOTIFY_MODE && sscanf (key, "undelete_notification_user_update%d_%d_%d_%d_%d", &user_id, &type, &owner, &place, &item) == 5 && place > 0 && item >= 0) {
      undelete_queries++;
      res = do_undelete_user_comment (user_id, type, owner, place, item);
    }
    break;
  case 'c':
    if (COMM_MODE && sscanf (key, "comm_updates%d_%d_%d", &type, &owner, &place) == 3 && place > 0) {
      delete_queries++;
      res = do_delete_place (type, owner, place);
    } else if (COMM_MODE && sscanf (key, "comm_update%d_%d_%d_%d", &type, &owner, &place, &item) == 4 && place > 0 && item > 0) {
      delete_queries++;
      res = do_delete_comment (type, owner, place, item);
    }
    break;
  case 'b':
    if (COMM_MODE && sscanf (key, "bookmark_%d_%d_%d:%d", &type, &owner, &place, &user_id) == 4) {
      res = do_add_del_bookmark (user_id, type, owner, place, 0);
    }
    break;
  case 'n':
    if (NOTIFY_MODE && sscanf (key, "notification_updates%d_%d_%d", &type, &owner, &place) == 3 && place > 0) {
      delete_queries ++;
      res = do_delete_place (type, owner, place);
    } else if (NOTIFY_MODE && sscanf (key, "notification_update%d_%d_%d_%d", &type, &owner, &place, &item) == 4 && place > 0) {
      delete_queries++;
      res = do_delete_comment (type, owner, place, item);
    } else if (NOTIFY_MODE && sscanf (key, "notification_user_update%d_%d_%d_%d_%d", &user_id, &type, &owner, &place, &item) == 5 && place > 0) {
      delete_queries++;
      res = do_delete_user_comment (user_id, type, owner, place, item);
    }

    break;
  }

  if (res > 0) {
    write_out (&c->Out, "DELETED\r\n", 9);
  } else {
    write_out (&c->Out, "NOT_FOUND\r\n", 11);
  }

  return 0;
}