#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  user ;
typedef  int /*<<< orphan*/  kfs_file_handle_t ;
struct TYPE_7__ {int user_cnt; int /*<<< orphan*/  total_photos; int /*<<< orphan*/  log_pos1_crc32; int /*<<< orphan*/  log_pos1; int /*<<< orphan*/  log_timestamp; } ;
struct TYPE_6__ {struct TYPE_6__* prev_used; struct TYPE_6__* next_used; } ;

/* Variables and functions */
 TYPE_1__* LRU_head ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* dl_malloc (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  h_users ; 
 TYPE_3__ header ; 
 int index_users ; 
 int /*<<< orphan*/  init_types () ; 
 int /*<<< orphan*/  jump_log_crc32 ; 
 int /*<<< orphan*/  jump_log_pos ; 
 int /*<<< orphan*/  jump_log_ts ; 
 int load_header (int /*<<< orphan*/ ) ; 
 int log_ts_exact_interval ; 
 int /*<<< orphan*/  map_int_int_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_intp_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  total_photos ; 
 int /*<<< orphan*/  try_init_local_uid () ; 
 int user_cnt ; 
 int /*<<< orphan*/  user_init (TYPE_1__*) ; 
 TYPE_1__* users ; 
 int verbosity ; 
 int /*<<< orphan*/  volumes ; 

int init_all (kfs_file_handle_t Index) {
  int i;

  if (verbosity > 1) {
    fprintf (stderr, "Init_all started\n");
  }

  log_ts_exact_interval = 1;

  map_int_int_init (&volumes);
  set_intp_init (&h_users);
  init_types();

  int f = load_header (Index);

  jump_log_ts = header.log_timestamp;
  jump_log_pos = header.log_pos1;
  jump_log_crc32 = header.log_pos1_crc32;

  user_cnt = index_users = header.user_cnt;
  total_photos = header.total_photos;

  if (user_cnt < 200000) {
    user_cnt = 200000;
  }

  assert (user_cnt >= 200000);
  user_cnt *= 1.1;
  //fix:
  //user_cnt = 20;

  while (user_cnt % 2 == 0 || user_cnt % 5 == 0) {
    user_cnt++;
  }

  users = dl_malloc (sizeof (user) * user_cnt);

  for (i = 0; i < user_cnt; i++) {
    user_init (&users[i]);
  }

  LRU_head = users;
  LRU_head->next_used = LRU_head->prev_used = LRU_head;

  if (f) {
    try_init_local_uid();
  }

  if (verbosity > 1) {
    fprintf (stderr, "Init_all finished\n");
  }

  return f;
}