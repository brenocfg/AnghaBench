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
struct forth_condition_stack {int top; } ;

/* Variables and functions */
 int MAX_ERROR_BUF_SIZE ; 
 int /*<<< orphan*/  add_lit_str (char*,void**,int*,int,char*) ; 
 scalar_t__ isspace (char) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  parse_token (char*,void**,int*,int,struct forth_condition_stack*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  vkprintf (int,char*,int,char*,int) ; 

int lex (char *value, int value_len, void **IP, int ip_size, char last_error[MAX_ERROR_BUF_SIZE]) {
  int i, j, k = 0, n = 0;
  vkprintf (3, "lex (\"%.*s\", ip_size = %d\n", value_len, value, ip_size);
  struct forth_condition_stack cond_stack;
  cond_stack.top = -1;
  for (i = 0; ; k++) {
    while (i < value_len && isspace (value[i])) {
      i++;
    }
    if (i >= value_len) {
      break;
    }

    if (value[i] == '"') {
      //read string literal in double quot
      i++;
      j = i;
      while (i < value_len && value[i] != '"') {
        i++;
      }
      if (i >= value_len) {
        strcpy (last_error, "lex: unclosed double quot");
        return -1;
      }
      value[i] = 0;
      if (!add_lit_str (value + j, IP, &n, ip_size, last_error)) {
        return -1;
      }
      i++;
      continue;
    }

    j = i;
    while (j < value_len && !isspace (value[j])) {
      j++;
    }
    value[j] = 0;
    if (!parse_token (value + i, IP, &n, ip_size, &cond_stack, last_error)) {
      int l = strlen (last_error);
      int o = MAX_ERROR_BUF_SIZE - l - 1;
      if (o > 0) {
        memset (last_error + l, 0, o + 1);
        snprintf (last_error + l, o , "\nlex: couldn't parse %d-th token (%s)", k, value + i);
      }
      return -1;
    }
    i = j + 1;
  }

  if (!parse_token ("BYE", IP, &n, ip_size, &cond_stack, last_error)) {
    return -1;
  }

  if (cond_stack.top >= 0) {
    strcpy (last_error, "unclosed if statement");
    return -1;
  }

  return n;
}