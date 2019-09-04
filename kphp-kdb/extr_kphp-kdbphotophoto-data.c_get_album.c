#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  local_id; } ;
typedef  TYPE_1__ user ;
typedef  int /*<<< orphan*/  actual_object ;

/* Variables and functions */
 size_t ALBUM_TYPE ; 
 int /*<<< orphan*/  NOAIO ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* conv_uid_get (int) ; 
 scalar_t__ debug_error ; 
 char* event_to_array (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int) ; 
 int get_fields (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  index_mode ; 
 int /*<<< orphan*/  load_user_metafile (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  return_fields ; 
 int /*<<< orphan*/ * types ; 
 scalar_t__ user_get_album (TYPE_1__*,int,int const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  user_loaded (TYPE_1__*) ; 
 int /*<<< orphan*/  write_only ; 

int get_album (int uid, int aid, const int force, char *fields, char **result) {
  assert (!index_mode && !write_only);

  user *u = conv_uid_get (uid);
  int fields_n = get_fields (&types[ALBUM_TYPE], fields);

  if (u == NULL || fields_n < 0) {
    return 0;
  }

  load_user_metafile (u, u->local_id, NOAIO);
  if (!user_loaded (u)) {
    return -2;
  }

  actual_object o;
  if (user_get_album (u, aid, force, &o) < 0) {
    return 0;
  }

  *result = event_to_array (&o, ALBUM_TYPE, return_fields, fields_n);

  if (debug_error) {
    return 0;
  }

  return 1;
}