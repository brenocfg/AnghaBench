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
struct tl_expression {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  client_command_generator ; 
 int /*<<< orphan*/  cstr_free (char**) ; 
 char* cstr_substr (char*,int,int) ; 
 struct tl_expression* expected_expr ; 
 scalar_t__ expected_type ; 
 struct tl_expression* find_expression (int) ; 
 int /*<<< orphan*/  isspace (char) ; 
 int /*<<< orphan*/  memcmp (char*,char*,int) ; 
 char** rl_completion_matches (char const*,int /*<<< orphan*/ ) ; 
 char* rl_line_buffer ; 
 int /*<<< orphan*/  tl_arg_generator ; 
 int /*<<< orphan*/  tl_command_generator ; 
 scalar_t__ tl_expression_get_argument_type (struct tl_expression*,char*) ; 
 int /*<<< orphan*/  tl_type_generator ; 

__attribute__((used)) static char **tl_completion (const char *text, int start, int end) {
  if (start == 0) {
    return rl_completion_matches (text, client_command_generator);
  }

  if ( (start == 1 && rl_line_buffer[0] == '(') || (start == 5 && !memcmp (rl_line_buffer, "help ", 5))) {
    return rl_completion_matches (text, tl_command_generator);
  }

  int j = start - 1;
  while (j > 0 && rl_line_buffer[j] != '(' && !isspace (rl_line_buffer[j])) {
    if (rl_line_buffer[j] == ')') {
      j = 0;
    }
    j--;
  }
  if (j > 0 && rl_line_buffer[j] == '(' && rl_line_buffer[j-1] == ':') {
    int i = j - 2;
    while (i > 0 && !isspace (rl_line_buffer[i])) {
      i--;
    }
    struct tl_expression *E = find_expression (i);
    if (E != NULL) {
      char *field_name = cstr_substr (rl_line_buffer, i + 1, j - 1);
      //kprintf ("field_name: %s\n", field_name);
      expected_type = tl_expression_get_argument_type (E, field_name);
      //kprintf ("expected_type: %s\n", expected_type);
      cstr_free (&field_name);
      if (expected_type) {
        return rl_completion_matches (text, tl_type_generator);
      }
    }
  }

  struct tl_expression *E = find_expression (start);
  if (E) {
    expected_expr = E;
    return rl_completion_matches (text, tl_arg_generator);
  }
  return NULL;
}