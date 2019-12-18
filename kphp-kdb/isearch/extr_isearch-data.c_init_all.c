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
typedef  int /*<<< orphan*/  q_info ;
typedef  int /*<<< orphan*/  kfs_file_handle_t ;
struct TYPE_4__ {int /*<<< orphan*/  log_pos1_crc32; int /*<<< orphan*/  log_pos1; int /*<<< orphan*/  log_timestamp; int /*<<< orphan*/  use_stemmer; int /*<<< orphan*/  created_at; } ;
struct TYPE_3__ {int prev_bucket; int next_bucket; scalar_t__ prev_used; scalar_t__ next_used; } ;

/* Variables and functions */
 int H_MUL ; 
 int MAX_S_LEN ; 
 int STAT_ST ; 
 char* alph ; 
 int /*<<< orphan*/  alph_n ; 
 int /*<<< orphan*/  common_spelling_errors ; 
 void* dl_malloc0 (int) ; 
 int /*<<< orphan*/  h_id ; 
 int /*<<< orphan*/  h_pref ; 
 int /*<<< orphan*/  h_word ; 
 TYPE_2__ header ; 
 int /*<<< orphan*/  hmap_ll_int_init (int /*<<< orphan*/ *) ; 
 int* hp ; 
 int /*<<< orphan*/  jump_log_crc32 ; 
 int /*<<< orphan*/  jump_log_pos ; 
 int /*<<< orphan*/  jump_log_ts ; 
 int load_index (int /*<<< orphan*/ ) ; 
 int log_ts_exact_interval ; 
 double** prob ; 
 int /*<<< orphan*/  process_errors (int /*<<< orphan*/ ,double) ; 
 TYPE_1__* q_entry ; 
 void* q_rev ; 
 int qr ; 
 int /*<<< orphan*/  ratingT ; 
 int /*<<< orphan*/  short_distance_errors ; 
 int /*<<< orphan*/  stem_init () ; 
 int /*<<< orphan*/  try_init_local_uid () ; 
 int /*<<< orphan*/  use_stemmer ; 

int init_all (kfs_file_handle_t Index) {
  log_ts_exact_interval = 1;

  hmap_ll_int_init (&h_pref);
  hmap_ll_int_init (&h_id);
#ifdef TYPES
  hmap_ll_int_init (&h_word);
#endif

  int f = load_index (Index);
  ratingT = header.created_at;
  use_stemmer = header.use_stemmer;

  jump_log_ts = header.log_timestamp;
  jump_log_pos = header.log_pos1;
  jump_log_crc32 = header.log_pos1_crc32;

  int i;
  qr = STAT_ST;
  q_entry = dl_malloc0 (sizeof (q_info) * (STAT_ST + qr));
  q_rev = dl_malloc0 (sizeof (int) * qr);
  for (i = 1; i < STAT_ST; i++) {
    q_entry[i].prev_bucket = i;
    q_entry[i].next_bucket = i;
  }
  q_entry[0].next_used = 0;
  q_entry[0].prev_used = 0;

  hp[0] = 1;
  for (i = 1; i < MAX_S_LEN; i++) {
    hp[i] = hp[i - 1] * H_MUL;
  }

#ifdef SLOW
  for (i = 0; i < 26; i++) {
    alph[alph_n++] = i + 'a';
  }

  for (i = 1072; i <= 1103; i++) {
    alph[alph_n++] = i;
  }
#else
  alph[alph_n++] = '?';
#endif

  process_errors (short_distance_errors, 0.5);
  process_errors (common_spelling_errors, 1.0);

  int j;
  for (i = 0; i < 128; i++) {
    for (j = 0; j < 128; j++) {
      prob[i][j] = (1.0 + prob[i][j]) * 0.5;
    }
  }

  stem_init();

  if (f) {
    try_init_local_uid();
  }
  return 1;
}