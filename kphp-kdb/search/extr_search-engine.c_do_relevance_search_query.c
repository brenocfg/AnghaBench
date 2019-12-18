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
struct value_buffer {int /*<<< orphan*/  (* output_int ) (struct value_buffer*,int) ;int /*<<< orphan*/  (* output_char ) (struct value_buffer*,char) ;int /*<<< orphan*/  (* output_item_id ) (struct value_buffer*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* output_hash ) (struct value_buffer*,int /*<<< orphan*/ ) ;} ;
struct connection {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  item_id; } ;

/* Variables and functions */
 scalar_t__ Q_hash_group_mode ; 
 scalar_t__ Q_limit ; 
 TYPE_1__** R ; 
 int* RV ; 
 int R_cnt ; 
 int R_tot ; 
 int /*<<< orphan*/  assert (int) ; 
 int do_perform_query (char const*,int) ; 
 int /*<<< orphan*/  extract_hash_item (TYPE_1__*) ; 
 char* parse_relevance_search_query (char*,int*,int*,int) ; 
 int /*<<< orphan*/  relevance_search_queries ; 
 int return_error (struct connection*,char const*,int,int,char*) ; 
 int /*<<< orphan*/  search_queries ; 
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
 int /*<<< orphan*/  value_buffer_init (struct value_buffer*,struct connection*,char const*,int,int,int) ; 
 int value_buffer_return (struct value_buffer*) ; 
 int /*<<< orphan*/  vkprintf (int,char*,int,char const*,int) ; 

int do_relevance_search_query (struct connection *c, const char *key, int len, int dog_len) {
  int i, Q_raw, err = 0;

  char *q_end = parse_relevance_search_query ((char *) key, &Q_raw, &err, 1);

  if (err < 0) {
    vkprintf (1, "parse_relevance_search_query (%.*s) returns error code %d.\n", len, key, err);
    return return_error (c, key, len, dog_len, q_end);
  }

  search_queries++;
  relevance_search_queries++;

  int res = do_perform_query (key, len);

  struct value_buffer b;
  if (!value_buffer_init (&b, c, key - dog_len, len + dog_len, Q_raw, 64)) {
    return 0;
  }
  if (Q_hash_group_mode) {
    assert (Q_limit > 0);
    b.output_int (&b, R_tot);
    for (i = 0; i < R_cnt; i++) {
      if (!value_buffer_flush (&b) ) { return -1; }
      b.output_char (&b, ',');
      b.output_item_id (&b, R[i]->item_id);
      b.output_char (&b, ',');
      b.output_int (&b, RV[i]);
      b.output_char (&b, ',');
      b.output_hash (&b, extract_hash_item (R[i]));
    }
    return value_buffer_return (&b);
  }

  b.output_int (&b, res);
  for (i = 0; i < R_cnt; i++) {
    if (!value_buffer_flush (&b) ) { return -1; }
    b.output_char (&b, ',');
    b.output_item_id (&b, R[i]->item_id);
    b.output_char (&b, ',');
    b.output_int (&b, RV[i]);
  }
  return value_buffer_return (&b);
}