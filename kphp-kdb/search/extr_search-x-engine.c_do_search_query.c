#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct value_buffer {int /*<<< orphan*/  (* output_int ) (struct value_buffer*,int) ;int /*<<< orphan*/  (* output_char ) (struct value_buffer*,char) ;int /*<<< orphan*/  (* output_item_id ) (struct value_buffer*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* output_hash ) (struct value_buffer*,int /*<<< orphan*/ ) ;} ;
struct search_query_heap_en {double cpu_time; int res; scalar_t__* query; } ;
struct connection {int dummy; } ;
struct TYPE_5__ {double cpu_time; } ;
struct TYPE_4__ {int /*<<< orphan*/  item_id; } ;

/* Variables and functions */
 int LAST_SEARCH_QUERY_BUFF_SIZE ; 
 scalar_t__ Q_hash_group_mode ; 
 scalar_t__ Q_limit ; 
 int /*<<< orphan*/  Q_raw ; 
 TYPE_1__** R ; 
 int /*<<< orphan*/ * RR ; 
 int R_cnt ; 
 int R_tot ; 
 scalar_t__ SEARCH_QUERY_HEAP_SIZE ; 
 TYPE_2__* SQH ; 
 scalar_t__ SQH_SIZE ; 
 int /*<<< orphan*/  assert (int) ; 
 int convert_rating (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  get_hash_item (TYPE_1__*) ; 
 double get_rusage_time () ; 
 scalar_t__* last_search_query ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,char const*,int) ; 
 char* parse_query (char*,int /*<<< orphan*/ *,int*) ; 
 int perform_query () ; 
 int return_one_key (struct connection*,char const*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  search_queries ; 
 int /*<<< orphan*/  search_query_heap_insert (struct search_query_heap_en*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcpy (scalar_t__*,char const*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 int /*<<< orphan*/  stub1 (struct value_buffer*,int) ; 
 int /*<<< orphan*/  stub10 (struct value_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub11 (struct value_buffer*,char) ; 
 int /*<<< orphan*/  stub12 (struct value_buffer*,int) ; 
 int /*<<< orphan*/  stub2 (struct value_buffer*,char) ; 
 int /*<<< orphan*/  stub3 (struct value_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct value_buffer*,char) ; 
 int /*<<< orphan*/  stub5 (struct value_buffer*,int) ; 
 int /*<<< orphan*/  stub6 (struct value_buffer*,char) ; 
 int /*<<< orphan*/  stub7 (struct value_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (struct value_buffer*,int) ; 
 int /*<<< orphan*/  stub9 (struct value_buffer*,char) ; 
 int /*<<< orphan*/  value_buffer_flush (struct value_buffer*) ; 
 int /*<<< orphan*/  value_buffer_init (struct value_buffer*,struct connection*,char const*,int,int /*<<< orphan*/ ,int) ; 
 int value_buffer_return (struct value_buffer*) ; 
 scalar_t__ verbosity ; 
 int /*<<< orphan*/  vkprintf (int,char*,...) ; 
 scalar_t__* zzmalloc (int) ; 

int do_search_query (struct connection *c, const char *key, int len, int dog_len) {
  static char buff[2048];
  int i = -1;
  int res;

  if (strncmp (key, "search", 6)) {
    return 0;
  }

  if (verbosity > 0) {
    fprintf (stderr, "got: %s\n", key);
  }

  res = 0;
  int r;
  char *q_end = parse_query ((char*) key, &Q_raw, &r);

  if (r < 0) {
    vkprintf (1, "parse_query (%.*s) returns error code %d.\n", len, key, r);
    vkprintf (1, "ERROR near '%.256s'\n", q_end);
    return return_one_key (c, key - dog_len, buff, sprintf (buff, "ERROR near '%.256s'\n", q_end));
  }

  R_cnt = 0;
  search_queries++;

  if (len < LAST_SEARCH_QUERY_BUFF_SIZE) {
    memcpy (last_search_query, key, len);
    last_search_query[len] = 0;
  } else {
    strcpy (last_search_query, "TOO LONG QUERY");
  }

  double perform_query_time = -get_rusage_time ();
  res = perform_query();
  perform_query_time += get_rusage_time ();

  if (SQH_SIZE < SEARCH_QUERY_HEAP_SIZE || SQH[1].cpu_time < perform_query_time) {
    struct search_query_heap_en E;
    E.query = zzmalloc (len+1);
    strcpy (E.query, key);
    E.cpu_time = perform_query_time;
    E.res = res;
    search_query_heap_insert (&E);
  }
  /*
  if (perform_query_time > max_perform_query_time) {
    max_perform_query_time = perform_query_time;
    strncpy (worst_search_query, key, STATS_SEARCH_QUERY_BUFFER_SIZE - 1);
    worst_search_query[STATS_SEARCH_QUERY_BUFFER_SIZE - 1] = 0;
    worst_search_query_res = res;
  }
  */

  if (verbosity > 0) {
    fprintf (stderr, "result = %d\n", res);
  }

  struct value_buffer b;
  if (!value_buffer_init (&b, c, key - dog_len, len + dog_len, Q_raw, 64)) {
    return -1;
  }
  if (Q_hash_group_mode) {
    assert (Q_limit > 0);
    b.output_int (&b, R_tot);
    for (i = 0; i < R_cnt; i++) {
      if (!value_buffer_flush (&b) ) { return -1; }
      b.output_char (&b, ',');
      b.output_item_id (&b, R[i]->item_id);
      b.output_char (&b, ',');
      b.output_int (&b, convert_rating (RR[i]));
      b.output_char (&b, ',');
      b.output_hash (&b, get_hash_item (R[i]));
    }
    return value_buffer_return (&b);
  }

  b.output_int (&b, res);
  for (i = 0; i < R_cnt; i++) {
    if (!value_buffer_flush (&b) ) { return -1; }
    b.output_char (&b, ',');
    b.output_item_id (&b, R[i]->item_id);
    b.output_char (&b, ',');
    b.output_int (&b, convert_rating (RR[i]));
  }
  return value_buffer_return (&b);
}