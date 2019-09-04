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
 int /*<<< orphan*/  READ_CHAR (char*,char) ; 
 int /*<<< orphan*/  READ_INT (char*,int) ; 
 int /*<<< orphan*/  READ_LONG (char*,unsigned long long) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  check_photo_id (int) ; 
 char* location_buf ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 char mode ; 
 int /*<<< orphan*/  save_location (char*,int,int,int,int,unsigned long long) ; 
 int user_loaded (int /*<<< orphan*/ *) ; 
 char* user_photo_get_location (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int*) ; 
 int user_photo_set_location (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ write_only ; 

int user_rotate_photo (user *u, int pid, int dir) {
  if ((dir != 1 && dir != 3) || !check_photo_id (pid)) {
    return 0;
  }

  if (write_only) {
    return 1;
  }

  assert (user_loaded (u));

  int len;
  char *loc = user_photo_get_location (u, pid, 0, 1, &len);

  if (loc == NULL) {
    return 0;
  }

  char *s = location_buf;

  if (len > 0 && loc[0] < 0) {
    int cur = -(loc[0] + mode) + 4 * sizeof (int) + 1;
    memcpy (s, loc, cur);
    s += cur;
    loc += cur;

    int cur_dir = 0;
    if ((s[-1] >= '1' && s[-1] <= '3') && (s[-2] >= 'w' && s[-2] <= 'z')) {
      cur_dir = s[-1];
      s--;
      (*location_buf)++;
    }

    if (s[-1] < 'w' || s[-1] > 'z') {
      *s++ = 'x';
      (*location_buf)--;
    }

    cur_dir += dir;
    if (cur_dir % 4) {
      *s++ = '0' + cur_dir % 4;
      (*location_buf)--;
    }
  }
  char *t = s++;

  char count = 0;
  int pass;
  int new_vid = 0, new_local_id = 0;
  char new_size = 0;
  char *loc_begin = loc;

  for (pass = 0; pass < 2; pass++) {
    loc = loc_begin;
    int old_vid = 0, old_local_id = 0, old_extra = 0, i;
    char old_size = 0, diff;
    unsigned long long old_secret = 0;

    for (i = len ? *loc++ : 0; i > 0; i--) {
      READ_CHAR(loc, old_size);
      assert (old_size);
      if (old_size < 0) {
        old_size *= -1;
        READ_CHAR(loc, diff);
        old_local_id += diff;
      } else {
        READ_INT(loc, old_vid);
        READ_INT(loc, old_local_id);
      }
      READ_INT(loc, old_extra);
      READ_LONG(loc, old_secret);

      int new_dir = (old_size >> 5) + dir;
      if ((new_dir >= 4) ^ pass) {
        save_location (s, ((new_dir & 3) << 5) + (old_size & 31), old_vid, old_local_id, old_extra, old_secret);
      }
    }
  }
  *t = count;
  assert ((len == 0 && count == 0) || *loc_begin == count);

  return user_photo_set_location (u, pid, 0, location_buf, (s - location_buf));
}