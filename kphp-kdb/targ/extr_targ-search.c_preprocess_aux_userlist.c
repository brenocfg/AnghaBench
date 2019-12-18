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
 unsigned int MAX_AUX_USERS ; 
 int /*<<< orphan*/ * User ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  aux_sort (int /*<<< orphan*/ ,long) ; 
 int* aux_userlist ; 
 int aux_userlist_size ; 
 int /*<<< orphan*/  aux_userlist_tag ; 
 int log_split_min ; 
 int log_split_mod ; 
 int max_uid ; 
 int /*<<< orphan*/  vkprintf (int,char*,long,int /*<<< orphan*/ ,int,int,int) ; 

int preprocess_aux_userlist (void) {
  long i, j;
  vkprintf (2, "preprocess_aux_userlist: size=%d tag=%d A=%d %d %d...\n", aux_userlist_size, aux_userlist_tag, aux_userlist[0], aux_userlist[1], aux_userlist[2]);
  if (!aux_userlist_size || !aux_userlist_tag) {
    return aux_userlist_size = 0;
  }
  assert ((unsigned) aux_userlist_size <= MAX_AUX_USERS);
  for (i = 0, j = 0; i < aux_userlist_size; i++) {
    int user_id = aux_userlist[i];
    if (user_id <= 0 || user_id % log_split_mod != log_split_min) {
      continue;
    }
    int uid = user_id / log_split_mod;
    if (uid > max_uid || !User[uid]) {
      continue;
    }
    aux_userlist[j++] = uid;
  }
  if (!j) {
    return aux_userlist_size = 0;
  }
  for (i = 1; i < j; i++) {
    if (aux_userlist[i] > aux_userlist[i-1]) {
      break;
    }
  }
  if (i < j) {
    aux_sort (0, j - 1);
  }
  aux_userlist_size = j;
  for (i = 1, j = 1; i < aux_userlist_size; i++) {
    if (aux_userlist[i] > aux_userlist[i-1]) {
      aux_userlist[j++] = aux_userlist[i];
    }
  }
  vkprintf (2, "AFTER preprocess_aux_userlist: size=%ld tag=%d A=%d %d %d...\n", j, aux_userlist_tag, aux_userlist[0], aux_userlist[1], aux_userlist[2]);
  return aux_userlist_size = j;
}