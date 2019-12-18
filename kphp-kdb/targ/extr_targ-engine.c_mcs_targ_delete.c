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

/* Variables and functions */
 int do_delete_addresses (int) ; 
 int do_delete_education (int) ; 
 int do_delete_groups (int) ; 
 int do_delete_interests (int,int) ; 
 int do_delete_langs (int) ; 
 int do_delete_military (int) ; 
 int do_delete_negative_groups (int) ; 
 int do_delete_positive_groups (int) ; 
 int do_delete_proposal (int) ; 
 int do_delete_schools (int) ; 
 int do_delete_user (int) ; 
 int do_delete_user_group (int,int) ; 
 int do_delete_user_lang (int,int) ; 
 int do_delete_work (int) ; 
 int /*<<< orphan*/  free_tmp_buffers (struct connection*) ; 
 int sscanf (char const*,char*,int*,...) ; 
 int /*<<< orphan*/  vkprintf (int,char*,char const*) ; 
 int /*<<< orphan*/  write_out (int /*<<< orphan*/ *,char*,int) ; 

int mcs_targ_delete (struct connection *c, const char *str, int len) {
  int user_id = -1, group_id = 0, lang_id = -1, type = 0, res = 0;

  vkprintf (2, "delete \"%s\"\n", str);
  free_tmp_buffers (c);
  
  switch (*str) {
  case 'a':
    if (sscanf (str, "address%d ", &user_id) == 1) {
      res = do_delete_addresses (user_id);
    }
    break;
  case 'c':
    if (sscanf (str, "company%d ", &user_id) == 1) {
      res = do_delete_work (user_id);
    }
    break;
  case 'e':
    if (sscanf (str, "education%d ", &user_id) == 1) {
      res = do_delete_education (user_id);
    }
    break;
  case 'i':
    if (sscanf (str, "interests%d#%d ", &user_id, &type) >= 1) {
      res = do_delete_interests (user_id, type);
    }
    break;
  case 'm':
    if (sscanf (str, "military%d ", &user_id) == 1) {
      res = do_delete_military (user_id);
    }
    break;
  case 'p':
    if (sscanf (str, "proposal%d ", &user_id) == 1) {
      res = do_delete_proposal (user_id);
    }
    break;
  case 's':
    if (sscanf (str, "school%d ", &user_id) == 1) {
      res = do_delete_schools (user_id);
    }
    break;
  case 'u':
    if (sscanf (str, "user_group%d_%d ", &user_id, &group_id) == 2) {
      res = do_delete_user_group (user_id, group_id);
    } else if (sscanf (str, "user_langs%d ", &user_id) == 1) {
      res = do_delete_langs (user_id);
    } else if (sscanf (str, "user_lang%d_%d ", &user_id, &lang_id) == 2) {
      res = do_delete_user_lang (user_id, lang_id);
    } else if (sscanf (str, "user_groups%d ", &user_id) == 1) {
      res = do_delete_groups (user_id);
    } else if (sscanf (str, "user_groups_positive%d ", &user_id) == 1) {
      res = do_delete_positive_groups (user_id);
    } else if (sscanf (str, "user_groups_negative%d ", &user_id) == 1) {
      res = do_delete_negative_groups (user_id);
    } else if (sscanf (str, "user%d ", &user_id) == 1) {
      res = do_delete_user (user_id);
    }
    break;
  }

  if (!res) {
    write_out (&c->Out, "NOT_FOUND\r\n", 11);
  } else {
    write_out (&c->Out, "DELETED\r\n", 9);
  }
  return 0;
}