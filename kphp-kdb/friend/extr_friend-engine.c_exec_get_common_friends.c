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
 int /*<<< orphan*/  MAX_USERLIST_NUM ; 
 int /*<<< orphan*/  free_tmp_buffers (struct connection*) ; 
 int get_common_friends (int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resultlist ; 
 int /*<<< orphan*/  return_one_key_list (struct connection*,char const*,int,int,int,int /*<<< orphan*/ ,int) ; 
 int sscanf (char const*,char*,int*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/ * userlist ; 

void exec_get_common_friends (struct connection *c, const char *str, int len) {
	free_tmp_buffers (c);
  int user_id = 0;
  int raw = *str == '%';
  int pos = 0;
  const char *str_orig = str;
  int len_orig = len;
  if ((sscanf (str, "common_friends%d,%d%n", &user_id, &userlist[0], &pos) >= 2 && pos > 0) ||
      (sscanf (str, "%%common_friends%d,%d%n", &user_id, &userlist[0], &pos) >= 2 && pos > 0)) {
    if (len != pos) {
    	return;
    }
  	int res = get_common_friends (user_id, 1, userlist, resultlist, MAX_USERLIST_NUM);
	  return_one_key_list (c, str_orig, len_orig, res, -raw, resultlist, res);
  }
}