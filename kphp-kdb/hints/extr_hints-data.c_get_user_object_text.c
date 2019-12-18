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
typedef  int /*<<< orphan*/  user ;

/* Variables and functions */
 int /*<<< orphan*/  NOAIO ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bad_requests ; 
 int /*<<< orphan*/  check_object_id (long long) ; 
 int /*<<< orphan*/  check_type (int) ; 
 int /*<<< orphan*/  check_user_id (int) ; 
 char* clean_str (char*) ; 
 int /*<<< orphan*/ * conv_user_id (int) ; 
 int get_local_user_id (int) ; 
 int /*<<< orphan*/ * load_user_metafile (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int user_get_object_local_id (int /*<<< orphan*/ *,int,long long) ; 
 char* user_get_object_name (int /*<<< orphan*/ *,int) ; 

int get_user_object_text (int user_id, int type, long long object_id, char **text) {
  if (!check_user_id (user_id) || !check_type (type) || !check_object_id (object_id)) {
    bad_requests++;
    return -1;
  }

  int local_user_id = get_local_user_id (user_id);
  if (local_user_id == 0) {
    return 0;
  }
  assert (local_user_id > 0);

  user *u = conv_user_id (user_id);
  assert (u != NULL);

  if (load_user_metafile (u, local_user_id, NOAIO) == NULL) {
    return -2;
  }

  int local_id = user_get_object_local_id (u, type, object_id);
  if (!local_id) {
    return 0;
  }

  char *name = user_get_object_name (u, local_id);
  if (name == NULL) {
    return 0;
  }

  *text = clean_str (name);
  return 1;
}