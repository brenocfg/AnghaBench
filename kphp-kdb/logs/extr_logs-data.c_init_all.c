#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  kfs_file_handle_t ;
typedef  int /*<<< orphan*/  field_desc ;
typedef  int /*<<< orphan*/  event ;
struct TYPE_18__ {int type; char* name; } ;
struct TYPE_17__ {TYPE_3__* root; } ;
struct TYPE_16__ {scalar_t__ index_type; scalar_t__ log_pos1_crc32; scalar_t__ log_pos1; scalar_t__ log_timestamp; scalar_t__ log_pos0_crc32; scalar_t__ log_pos0; scalar_t__ log_timestamp0; } ;
struct TYPE_15__ {int type; int /*<<< orphan*/  name; } ;
struct TYPE_12__ {int /*<<< orphan*/  dtype; } ;
struct TYPE_14__ {TYPE_1__ tok; } ;
struct TYPE_13__ {int /*<<< orphan*/ * name; TYPE_5__* fields; } ;

/* Variables and functions */
 int FN ; 
 int INDEX_TYPE ; 
 scalar_t__ IS_STR (int /*<<< orphan*/ ) ; 
 int MAX_EV ; 
 int MAX_EVENT_MEM ; 
 int MAX_TYPE ; 
 int /*<<< orphan*/  add_field (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* ans ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * common_field_names ; 
 int /*<<< orphan*/ * common_field_types ; 
 int common_fields ; 
 void* dl_malloc (int) ; 
 int /*<<< orphan*/ * dl_strdup (char*) ; 
 TYPE_7__ dump_expr ; 
 scalar_t__ dump_mode ; 
 char* dump_query ; 
 int dump_type ; 
 TYPE_9__* empty_desc ; 
 void* eq ; 
 void* events_mem ; 
 int evm_mx ; 
 int /*<<< orphan*/  exit (int) ; 
 char* expression_compile (TYPE_7__*,char*,TYPE_2__*) ; 
 int /*<<< orphan*/ * field_names ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ from_ts ; 
 TYPE_6__ header ; 
 scalar_t__ index_mode ; 
 scalar_t__ jump_log_crc32 ; 
 scalar_t__ jump_log_pos ; 
 scalar_t__ jump_log_ts ; 
 int load_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_stat_queries () ; 
 scalar_t__* log_crc32 ; 
 scalar_t__* log_position ; 
 scalar_t__* log_timestamp ; 
 int log_ts_exact_interval ; 
 int /*<<< orphan*/  map_int_int_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  map_ll_int_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  map_type_id ; 
 int max_memory ; 
 int mean_event_size ; 
 int /*<<< orphan*/ * q_st_int ; 
 int /*<<< orphan*/ * q_st_ll ; 
 int query_memory ; 
 int /*<<< orphan*/  split (char*,char**,int*,int) ; 
 int sscanf (char*,char*,int*,int*) ; 
 TYPE_5__* std_desc ; 
 scalar_t__* std_t ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__* time_table_log_crc32 ; 
 scalar_t__* time_table_log_position ; 
 scalar_t__* time_table_log_timestamp ; 
 int time_table_log_timestamp_size ; 
 TYPE_3__* tree_conv (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  try_init_local_uid () ; 
 TYPE_2__* types ; 
 int /*<<< orphan*/  v_int ; 
 int /*<<< orphan*/  vector_init (scalar_t__*) ; 
 scalar_t__ write_only ; 

int init_all (kfs_file_handle_t Index) {
  assert (sizeof (long long) == sizeof (double));

  log_ts_exact_interval = 1;

  MAX_EVENT_MEM = max_memory - query_memory;
  MAX_EV = MAX_EVENT_MEM / mean_event_size;
  evm_mx = MAX_EVENT_MEM - 5;
  assert (MAX_EVENT_MEM >= (1 << 26));

  vector_init (log_position);
  vector_init (log_timestamp);
  vector_init (log_crc32);

  vector_init (time_table_log_position);
  vector_init (time_table_log_timestamp);
  vector_init (time_table_log_crc32);

  map_ll_int_init (&map_type_id);

  if (!write_only) {
    events_mem = dl_malloc (MAX_EVENT_MEM);
    eq = dl_malloc (sizeof (event *) * MAX_EV);
    ans = dl_malloc (sizeof (int) * MAX_EV);
  }

  int i;
  for (i = 0; i < FN; i += 1 + std_t[i]) {
    std_desc[i].type = i - FN;
    std_desc[i].name = field_names[i];

    empty_desc[i].type = i - FN;
    empty_desc[i].name = "";
  }

  /* init virtual event */
  types[0].name = dl_strdup ("virtual_event");
  types[0].fields = dl_malloc (sizeof (field_desc) * FN);
  for (i = 0; i < FN; i += 1 + std_t[i]) {
    types[0].fields[i] = std_desc[i];
  }
  types[0].fields += FN;
  for (i = 0; i < common_fields; i++) {
    add_field (types, common_field_names[i], common_field_types[i]);
  }

  for (i = 0; i < FN; i += 1 + std_t[i]) {
    if (std_t[i]) {
      map_ll_int_init (&q_st_ll[i]);
    } else {
      map_int_int_init (&q_st_int[i]);
    }
  }

  int f = load_index (Index);

  if (dump_mode) {
    load_stat_queries();

    assert (INDEX_TYPE);
    if (header.index_type == 0) {
      fprintf (stderr, "You need to generate new index first.\n");
      exit (1);
    }
    int i;
    for (i = 0; i + 1 < time_table_log_timestamp_size && time_table_log_timestamp[i + 1] < from_ts; i++) {
    }

    if (strlen (dump_query) == 0) {
      fprintf (stderr, "Dump query can't be empty.\n");
      exit (1);
    }

    char *qs[3];
    int qn;
    split (dump_query, qs, &qn, 2);
    if (qn == 0) {
      fprintf (stderr, "Too much commas in dump query.\n");
      exit (1);
    }

    if (qn == 2 && strcmp (qs[1], "1")) {
      dump_query = qs[1];
    } else {
      dump_query = NULL;
    }

    int pos;
    if (sscanf (qs[0], "%d%n", &dump_type, &pos) != 1 || qs[0][pos]) {
      fprintf (stderr, "Can't parse [%s] as integer.\n", qs[0]);
      exit (1);
    }

    if (!(0 <= dump_type && dump_type < MAX_TYPE)) {
      fprintf (stderr, "Dump_type [%d] not in range [0;%d].\n", dump_type, MAX_TYPE - 1);
      exit (1);
    }

    if (dump_type != 0 && types[dump_type].name == NULL) {
      fprintf (stderr, "Dump_type [%d] is unknown.\n", dump_type);
      exit (1);
    }

    if (dump_query != NULL) {
      char *err = expression_compile (&dump_expr, dump_query, &types[dump_type]);
      if (err != NULL) {
        fprintf (stderr, "Cannot compile expression [%s] : error [%s]\n", dump_query, err);
        exit (1);
      }

      if (IS_STR(dump_expr.root->tok.dtype)) {
        fprintf (stderr, "Cannot convert result of dump_query[%s] (string) to int\n", dump_query);
        exit (1);
      }
      dump_expr.root = tree_conv (dump_expr.root, v_int);
    }

    jump_log_ts = time_table_log_timestamp[i];
    jump_log_pos = time_table_log_position[i];
    jump_log_crc32 = time_table_log_crc32[i];
//    fprintf (stderr, "%d %lld %d\n", jump_log_ts, jump_log_pos, jump_log_crc32);
  } else if (index_mode && INDEX_TYPE >= 1 && header.index_type == 0) {
    jump_log_ts = 0;
    jump_log_pos = 0;
    jump_log_crc32 = 0;
  } else if (write_only && !index_mode) {
    jump_log_ts = header.log_timestamp0;
    jump_log_pos = header.log_pos0;
    jump_log_crc32 = header.log_pos0_crc32;
  } else {
    jump_log_ts = header.log_timestamp;
    jump_log_pos = header.log_pos1;
    jump_log_crc32 = header.log_pos1_crc32;
  }
//  fprintf (stderr, "%d %lld %d\n", jump_log_ts, jump_log_pos, jump_log_crc32);

  if (f) {
    try_init_local_uid();
  }
  return f;
}