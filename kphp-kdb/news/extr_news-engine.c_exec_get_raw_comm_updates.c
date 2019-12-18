#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct keep_mc_store {int user_id; int len; } ;
struct connection {TYPE_1__* Tmp; } ;
struct TYPE_3__ {scalar_t__ start; } ;

/* Variables and functions */
 int MAX_QUERY ; 
 int* Q ; 
 int QL ; 
 scalar_t__ R ; 
 scalar_t__ R_end ; 
 int /*<<< orphan*/  advance_read_ptr (TYPE_1__*,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  clear_result_buffer () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,...) ; 
 int np_parse_list_str (int*,int,int,char const*,int) ; 
 int prepare_raw_comm_updates (int,int,int,int,int) ; 
 int read_in (TYPE_1__*,int*,int) ; 
 int return_one_key_list (struct connection*,char const*,int,int,int,scalar_t__,scalar_t__) ; 
 int sscanf (char const*,char*,int*,int*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int strtol (char const*,char**,int) ; 
 int verbosity ; 

__attribute__((used)) static int exec_get_raw_comm_updates (struct connection *c, const char *key, int key_len, int dog_len) {
  int user_id;
  int st_time = 0, end_time = 0, x = 0, raw = 0;
  char *ptr;

  struct keep_mc_store *Data = 0;

  if (c->Tmp) {
    Data = (struct keep_mc_store *) c->Tmp->start;
  }

  if (*key == '%') {
    raw = 1;
  }

  if ((sscanf (key+raw, "raw_comm_updates[%d,%d]:%n", &st_time, &end_time, &x) >= 2 ||
       sscanf (key+raw, "raw_comm_updates%n%d", &x, &user_id) >= 1) && x > 0) {
    x += raw;
    ptr = 0;
    user_id = strtol (key+x, &ptr, 10);


    if (user_id < 0 && ptr == key + key_len && Data && user_id == Data->user_id && Data->len) {
      if (verbosity > 1) {
        fprintf (stderr, "found userlist %d, %d entries\n", user_id, Data->len);
      }

      advance_read_ptr (c->Tmp, sizeof (struct keep_mc_store));
      QL = Data->len;
      if (QL > MAX_QUERY) { QL = MAX_QUERY; }
      x = read_in (c->Tmp, Q, QL*12);
      assert (x == QL*12);
      if (verbosity > 1 && QL > 0) {
        fprintf (stderr, "first entry: %d_%d_%d\n", Q[0], Q[1], Q[2]);
      }
    } else {
      QL = np_parse_list_str (Q, MAX_QUERY, 3, key + x, key_len - x);
    }

    clear_result_buffer ();
    int i, best = -1;
    QL *= 3;
    for (i = 0; i < QL; i += 3) {
      int res = prepare_raw_comm_updates (Q[i], Q[i+1], Q[i+2], st_time, end_time);
      if (verbosity > 1) {
        fprintf (stderr, "prepare_raw_comm_updates(%d_%d_%d) = %d\n", Q[i], Q[i+1], Q[i+2], res);
      }
      if (res > best) {
        best = res;
      }
    }
    if (best >= 0) {
      return return_one_key_list (c, key - dog_len, key_len + dog_len, /*(R_end - R) / 9*/ 0x7fffffff, -raw, R, R_end - R);
    }
  }
  return 0;
}