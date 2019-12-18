#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  value_buff ;
struct connection {int dummy; } ;
struct TYPE_4__ {int random_tag; int type; int owner; int place; int user; int item; int date; } ;
struct TYPE_3__ {int pos; int num; } ;

/* Variables and functions */
 TYPE_2__* RR ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,struct connection*,char const*,int,int) ; 
 TYPE_1__* notify_groups ; 
 int prepare_notify_groups (int,int,int,int,int,int,int,int*,int*) ; 
 int return_one_key_flags (struct connection*,char const*,char*,int) ; 
 int snprintf (char*,int,char*,...) ; 
 int sscanf (char const*,char*,int*,int*,int*,int*,int*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 

__attribute__((used)) static int exec_get_notification_updates (struct connection *c, const char *key, int key_len, int dog_len) {
  int user_id;
  int mask = -1, timestamp = 0, end_date = 0, raw = 0, date = 0, grouping = 0, limit = 0;

  static char value_buff[10000000];
  char *ptr = value_buff;
  char *end_ptr = value_buff + sizeof (value_buff);

  if (verbosity >= 2) {
    fprintf (stderr, "exec_get_notifications (%p, %s, %d, %d)\n", c, key, key_len, dog_len);
  }

  if (*key == '%') {
    raw = 1;
  }

  if (sscanf (key+raw, "notification_updates%d_%d,%d_%d>%d#%d:%d", &mask, &date, &end_date, &grouping, &timestamp, &limit, &user_id) == 7 ||
      sscanf (key+raw, "notification_updates%d_%d,%d_%d>%d:%d", &mask, &date, &end_date, &grouping, &timestamp, &user_id) == 6 ||
      sscanf (key+raw, "notification_updates%d_%d,%d_%d#%d:%d", &mask, &date, &end_date, &grouping, &limit, &user_id) == 6 ||
      sscanf (key+raw, "notification_updates%d_%d,%d_%d:%d", &mask, &date, &end_date, &grouping, &user_id) == 5) {
  } else {
    return 0;
  }

  int found, total_groups;
  int x = prepare_notify_groups (user_id, mask, date, end_date, grouping, timestamp, limit, &found, &total_groups);
  if (x < 0) {
    return 0;
  }

  int i;
  ptr += snprintf (ptr, end_ptr - ptr, "a:%d:{", x);

  for (i = 0; i < total_groups; i++) {
    char s[100];
    int cur_pos = notify_groups[i].pos;
    int tpos = (notify_groups[i].num > grouping) ? cur_pos + grouping : cur_pos + notify_groups[i].num;
    assert (tpos <= found);
    if (RR[cur_pos].random_tag < 0 && !grouping) {
      continue;
    }

    ptr += snprintf (ptr, end_ptr - ptr, "i:%d;a:%d:{", i, 5);
    ptr += snprintf (ptr, end_ptr - ptr, "i:0;i:%d;i:1;i:%d;i:2;i:%d;", RR[cur_pos].type, RR[cur_pos].owner, RR[cur_pos].place);
    if (!grouping) {
      int l = snprintf (s, 100, "%d_%d", RR[cur_pos].user, RR[cur_pos].item);
      ptr += snprintf (ptr, end_ptr - ptr, "i:3;s:%d:\"%s\";i:4;i:%d;", l, s, RR[cur_pos].date);
    } else {
      int j;
      int total = notify_groups[i].num;
      if (RR[cur_pos].random_tag <= 0) {
        total = -RR[cur_pos].random_tag;
        if (tpos < cur_pos + notify_groups[i].num) {
          tpos ++;
        }
        cur_pos ++;
      }
      for (j = 3; j < 5; j++) {
        ptr += snprintf (ptr, end_ptr - ptr, "i:%d;a:%d:{i:0;i:%d;", j, tpos - cur_pos + 1, total);
        int k;
        for (k = cur_pos; k < tpos; k++) {
          if (j == 3) {
            int l = snprintf (s, 100, "%d_%d", RR[k].user, RR[k].item);
            ptr += snprintf (ptr, ptr - end_ptr, "i:%d;s:%d:\"%s\";", k - cur_pos + 1, l, s);
          } else {
            ptr += snprintf (ptr, ptr - end_ptr, "i:%d;i:%d;", k - cur_pos + 1, RR[k].date);
          }
        }
        ptr += snprintf (ptr, end_ptr - ptr, "}");
      }
    }
    ptr += snprintf (ptr, end_ptr - ptr, "}");
  }

  ptr += snprintf (ptr, end_ptr - ptr, "}");
  if (end_ptr > ptr) {
    return return_one_key_flags (c, key-dog_len, value_buff, ptr - value_buff);
  }
  return 0;
}