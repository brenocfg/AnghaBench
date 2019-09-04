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
struct tl_compiler {int dummy; } ;
struct tl_buffer {char* buff; int /*<<< orphan*/  pos; } ;
typedef  enum tl_schema_split_state { ____Placeholder_tl_schema_split_state } tl_schema_split_state ;

/* Variables and functions */
 int /*<<< orphan*/  isalpha (char const) ; 
 int /*<<< orphan*/  isspace (char const) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 
 int /*<<< orphan*/  tl_add_expression (struct tl_compiler*,int,char*) ; 
 int tl_failfp (struct tl_compiler*,char const*,char const*,char*,...) ; 
 int /*<<< orphan*/  tl_string_buffer_append_char (struct tl_buffer*,char const) ; 
 int /*<<< orphan*/  tl_string_buffer_free (struct tl_buffer*) ; 
 int /*<<< orphan*/  tl_string_buffer_init (struct tl_buffer*) ; 
#define  tsss_after_slash 131 
#define  tsss_expression 130 
#define  tsss_line_comment 129 
#define  tsss_start_expression 128 

__attribute__((used)) static int tl_schema_split (struct tl_compiler *C, const char *input) {
  int section = 0;
  const char *s;
  struct tl_buffer b;
  tl_string_buffer_init (&b);

  enum tl_schema_split_state state = tsss_start_expression;
  for (s = input; *s; s++) {
    switch (state) {
    case tsss_start_expression:
      if (isspace (*s)) {
      } else if (*s == '/') {
        state = tsss_after_slash;
      } else if (isalpha (*s)) {
        b.pos = 0;
        tl_string_buffer_append_char (&b, *s);
        state = tsss_expression;
      } else if (*s == '-') {
        if (!strncmp (s, "---functions---", 15)) {
          if (++section > 1) {
            tl_string_buffer_free (&b);
            return tl_failfp (C, input, s, "too many ---functions--- sections");
          }
          s += 14;
        } else {
          tl_string_buffer_free (&b);
          return tl_failfp (C, input, s, "expected ---functions---");
        }
      } else {
        tl_string_buffer_free (&b);
        return tl_failfp (C, input, s, "illegal first expression's character (%c)", *s);
      }
    break;
    case tsss_after_slash:
      if (*s == '/') {
        state = tsss_line_comment;
      } else {
        tl_string_buffer_free (&b);
        return tl_failfp (C, input, s, "expected second slash, but %c found", *s);
      }
    break;
    case tsss_line_comment:
      if (*s == '\n') {
        state = tsss_start_expression;
      }
    break;
    case tsss_expression:
      if (*s == ';') {
        tl_string_buffer_append_char (&b, 0);
        tl_add_expression (C, section, b.buff);
        state = tsss_start_expression;
      } else if (isspace (*s)) {
        if (' ' != b.buff[b.pos-1]) {
          tl_string_buffer_append_char (&b, ' ');
        }
      } else {
        tl_string_buffer_append_char (&b, *s);
      }
    break;
    }
  }

  tl_string_buffer_free (&b);

  if (state == tsss_expression) {
    return tl_failfp (C, input, s, "last expression doesn't end by semicolon");
  }

  if (state == tsss_after_slash) {
    return tl_failfp (C, input, s, "found EOF, but expected second slash");
  }

  if (!section) {
    return tl_failfp (C, input, s, "don't find section '---functions---'");
  }

  return 0;
}