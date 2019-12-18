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
 int /*<<< orphan*/  WRITE_INT (char*,int) ; 
 int /*<<< orphan*/  WRITE_STRING (char*,char*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_photo (char*,int) ; 
 char* location_buf ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 char mode ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  user_loaded (int /*<<< orphan*/ *) ; 
 char* user_photo_get_location (int /*<<< orphan*/ *,int,int,int,int*) ; 
 int user_photo_set_location (int /*<<< orphan*/ *,int,int,char*,int) ; 
 scalar_t__ write_only ; 

int user_add_photo_location (user *u, int pid, int original, int sid, int sid2, int orig_oid, int orig_aid, char *photo) {
//  dbg ("user_add_photo_location %d: photo_id = %d, photo = %s\n", u->id, pid, photo);

  if (write_only) {
    return 1;
  }

  assert (user_loaded (u));
  int l = strlen (photo);
  assert (check_photo (photo, l));

  int len;
  char *loc = user_photo_get_location (u, pid, original, 1, &len);

  if (loc == NULL) {
    return 0;
  }

  char *s = location_buf;
  if (len > 0 && loc[0] < 0) {
    int cur = -(loc[0] + mode) + 4 * sizeof (int) + 1;
    len -= cur;
    loc += cur;
  }

  *s++ = -l - mode;
  WRITE_INT(s, sid);
  WRITE_INT(s, sid2);
  WRITE_INT(s, orig_oid);
  WRITE_INT(s, orig_aid);
  WRITE_STRING(s, photo);

  if (len == 0) {
    *s++ = 0;
  } else {
    memcpy (s, loc, len);
  }

  return user_photo_set_location (u, pid, original, location_buf, (s - location_buf) + len);
}