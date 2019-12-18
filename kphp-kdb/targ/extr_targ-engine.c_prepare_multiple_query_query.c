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
struct connection {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_query_list () ; 
 scalar_t__ compile_add_query (char**) ; 
 int /*<<< orphan*/  complete_long_query (struct connection*,int) ; 
 scalar_t__ load_temp_data (struct connection*) ; 
 scalar_t__ parse_search_extras (char const*) ; 
 int /*<<< orphan*/  parse_search_query_termination (char*) ; 
 int /*<<< orphan*/  register_long_query (char const*,int) ; 
 int /*<<< orphan*/  return_one_key (struct connection*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stats_buff ; 
 scalar_t__ strtol (char*,char**,int) ; 
 scalar_t__ tag_id ; 
 char* value_buff ; 

int prepare_multiple_query_query (struct connection *c, const char *start, const char *key, int key_len) {
  char *cur = (char *) parse_search_extras (start), *q_ptr, *q_start = cur + 1;
  if (*cur != '(') {
    return -1;
  }
  register_long_query (key, key_len);
  clear_query_list ();
  char *q_err = 0;
  if (load_temp_data (c) > 0 && cur[1] >= '0' && cur[1] <= '9' && strtol (cur + 1, &q_start, 10) == tag_id) {
    q_ptr = value_buff;
    if (compile_add_query (&q_ptr)) {
      while (*q_ptr == ';' || *q_ptr == '\n') {
        q_ptr++;
        if (!compile_add_query (&q_ptr)) {
          q_err = q_ptr;
          break;
        }
      }
    }
    if (!q_err) {
      if (*q_ptr) {
        q_err = q_ptr;
      } else if (*q_start++ != ';') {
        q_err = q_start - 1;
      }
    }
  }
  q_ptr = q_start;
  if (!q_err && compile_add_query (&q_ptr)) {
    while (*q_ptr == ';') {
      q_ptr++;
      if (!compile_add_query (&q_ptr)) {
        q_err = q_ptr;
        break;
      }
    }
  }
  parse_search_extras (start);
  if (!q_err && !parse_search_query_termination (q_ptr)) {
    q_err = q_ptr;
  }
  if (q_err) {
    complete_long_query (c, -1);
    return_one_key (c, key, stats_buff, sprintf (stats_buff, "ERROR near '%.256s'\n", q_err));
    return 0;
  } else {
    return 1;
  }
}