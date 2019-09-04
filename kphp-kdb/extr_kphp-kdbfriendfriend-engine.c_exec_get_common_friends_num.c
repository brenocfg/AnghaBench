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
struct connection {int dummy; } ;

/* Variables and functions */
 int MAX_USERLIST_NUM ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  get_common_friends_num (int,int,int*,int /*<<< orphan*/ ) ; 
 int get_saved_userlist (struct connection*,int) ; 
 int /*<<< orphan*/  resultlist ; 
 int /*<<< orphan*/  return_one_key_list (struct connection*,char const*,int,int,int,int /*<<< orphan*/ ,int) ; 
 int sscanf (char const*,char*,int*,int*) ; 
 int* userlist ; 

void exec_get_common_friends_num (struct connection *c, const char *str, int len) {
  int user_id = 0;
  int raw = *str == '%';
  int pos = 0;
  const char *str_orig = str;
  int len_orig = len;
  if ((sscanf (str, "common_friends_num%d:%n", &user_id, &pos) >= 1 && pos > 0) ||
      (sscanf (str, "%%common_friends_num%d:%n", &user_id, &pos) >= 1 && pos > 0)) {
    str += pos;
    len -= pos;
    int user_num = 0;
    if (*str == '-') {
      int t;
      if (sscanf (str, "%d%n", &t, &pos) < 1) {
        return;
      }
      if (pos != len) {
        return;
      }
      user_num = get_saved_userlist (c, t);
    } else {
      while (1) {
        if (sscanf (str, "%d%n", &userlist[user_num++], &pos) < 1) {
          return;
        }
        str += pos;
        len -= pos;
        if (!len) {
          break;
        }
        if (user_num == MAX_USERLIST_NUM || *str != ',') {
          return;
        }
        str ++;
        len --;
      }
    }
    assert (user_num <= MAX_USERLIST_NUM);
    get_common_friends_num (user_id, user_num, userlist, resultlist);
    return_one_key_list (c, str_orig, len_orig, 1, -raw, resultlist, user_num);
  }
}