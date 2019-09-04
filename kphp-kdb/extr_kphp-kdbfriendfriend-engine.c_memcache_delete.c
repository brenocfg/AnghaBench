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
struct connection {int /*<<< orphan*/  Out; } ;
typedef  int /*<<< orphan*/  privacy_key_t ;

/* Variables and functions */
 int binlog_disabled ; 
 int do_delete_all_friend_requests (int) ; 
 int do_delete_friend (int,int) ; 
 int do_delete_friend_category (int,int) ; 
 int do_delete_friend_request (int,int) ; 
 int do_delete_privacy (int,int /*<<< orphan*/ ) ; 
 int do_delete_user (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  parse_privacy_key (char const*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ reverse_friends_mode ; 
 int sscanf (char const*,char*,int*,...) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ verbosity ; 
 int /*<<< orphan*/  write_out (int /*<<< orphan*/ *,char*,int) ; 

int memcache_delete (struct connection *c, const char *key, int key_len) {
  int user_id, arg = 0;
  privacy_key_t privacy_key;

  if (verbosity > 0) {
    fprintf (stderr, "delete \"%s\"\n", key);
  }

  int res = -1;

  if (binlog_disabled == 2 || reverse_friends_mode) {
    write_out (&c->Out, "NOT_FOUND\r\n", 11);
    return 0;
  }

  switch (*key) {
  case 'u':
    if (sscanf (key, "user%d ", &user_id) == 1) {
      res = do_delete_user (user_id);
    }
    break;
  case 'f':
    if (sscanf (key, "friend_cat%d_%d ", &user_id, &arg) == 2) {
      res = do_delete_friend_category (user_id, arg);
    }
    if (sscanf (key, "friendreq%d_%d ", &user_id, &arg) == 2) {
      res = do_delete_friend_request (user_id, arg);
    }
    if (sscanf (key, "friend%d_%d ", &user_id, &arg) == 2) {
      res = do_delete_friend (user_id, arg);
    }
    break;
  case 'p':
    if (sscanf (key, "privacy%d_%n", &user_id, &arg) >= 1 && parse_privacy_key (key+arg, &privacy_key, 1) > 0) {
      res = do_delete_privacy (user_id, privacy_key);
    }
    break;
  case 'r':
    if (sscanf (key, "requests%d ", &user_id) == 1) {
      res = do_delete_all_friend_requests (user_id);
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