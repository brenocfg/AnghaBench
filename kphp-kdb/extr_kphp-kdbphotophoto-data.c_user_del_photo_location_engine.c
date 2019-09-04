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
 int /*<<< orphan*/  assert (char) ; 
 char* location_buf ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 char mode ; 
 int /*<<< orphan*/  save_location (char*,char,int,int,int,unsigned long long) ; 
 char user_loaded (int /*<<< orphan*/ *) ; 
 char* user_photo_get_location (int /*<<< orphan*/ *,int,int,int,int*) ; 
 int user_photo_set_location (int /*<<< orphan*/ *,int,int,char*,int) ; 
 scalar_t__ write_only ; 

int user_del_photo_location_engine (user *u, int pid, int original, char size, int rotate) {
  if ((size != -1 && size < 'a') || size > 'z' || rotate < -1 || rotate > 3) {
    return 0;
  }

  if (write_only) {
    return 1;
  }

  assert (user_loaded (u));

  int len;
  char *loc = user_photo_get_location (u, pid, original, 1, &len);

  if (loc == NULL) {
    return 0;
  }

  char *s = location_buf;

  if (len > 0 && loc[0] < 0) {
    int cur = -(loc[0] + mode) + 4 * sizeof (int) + 1;
    memcpy (s, loc, cur);
    s += cur;
    loc += cur;
  }
  char *t = s++;

  char count = 0;
  int old_vid = 0, old_local_id = 0, old_extra = 0, new_vid = 0, new_local_id = 0, i;
  char old_size = 0, new_size = 0, diff;
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
    if ((rotate != -1 && rotate != (old_size >> 5)) || (size != -1 && size - 'a' + 1 != (old_size & 31))) {
      save_location (s, old_size, old_vid, old_local_id, old_extra, old_secret);
    }
  }
  *t = count;

  return user_photo_set_location (u, pid, original, location_buf, (s - location_buf));
}