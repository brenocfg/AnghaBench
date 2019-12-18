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
struct jv_parser {int dummy; } ;
typedef  int /*<<< orphan*/  jv ;

/* Variables and functions */
 int /*<<< orphan*/  jv_copy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_invalid_get_msg (int /*<<< orphan*/ ) ; 
 scalar_t__ jv_invalid_has_msg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_invalid_with_msg (int /*<<< orphan*/ ) ; 
 scalar_t__ jv_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_parser_next (struct jv_parser*) ; 
 int /*<<< orphan*/  jv_parser_set_buf (struct jv_parser*,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_string (char*) ; 
 int /*<<< orphan*/  jv_string_fmt (char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  jv_string_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parser_free (struct jv_parser*) ; 
 int /*<<< orphan*/  parser_init (struct jv_parser*,int /*<<< orphan*/ ) ; 

jv jv_parse_sized(const char* string, int length) {
  struct jv_parser parser;
  parser_init(&parser, 0);
  jv_parser_set_buf(&parser, string, length, 0);
  jv value = jv_parser_next(&parser);
  if (jv_is_valid(value)) {
    jv next = jv_parser_next(&parser);
    if (jv_is_valid(next)) {
      // multiple JSON values, we only wanted one
      jv_free(value);
      jv_free(next);
      value = jv_invalid_with_msg(jv_string("Unexpected extra JSON values"));
    } else if (jv_invalid_has_msg(jv_copy(next))) {
      // parser error after the first JSON value
      jv_free(value);
      value = next;
    } else {
      // a single valid JSON value
      jv_free(next);
    }
  } else if (jv_invalid_has_msg(jv_copy(value))) {
    // parse error, we'll return it
  } else {
    // no value at all
    jv_free(value);
    value = jv_invalid_with_msg(jv_string("Expected JSON value"));
  }
  parser_free(&parser);

  if (!jv_is_valid(value) && jv_invalid_has_msg(jv_copy(value))) {
    jv msg = jv_invalid_get_msg(value);
    value = jv_invalid_with_msg(jv_string_fmt("%s (while parsing '%s')",
                                              jv_string_value(msg),
                                              string));
    jv_free(msg);
  }
  return value;
}