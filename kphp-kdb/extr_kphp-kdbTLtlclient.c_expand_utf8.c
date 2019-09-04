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

/* Variables and functions */
 int /*<<< orphan*/  log_str (char*) ; 
 int parse_bool (char*) ; 
 int /*<<< orphan*/  tl_set_expand_utf8 (int) ; 

int expand_utf8 (char *s) {
  int b = parse_bool (s);
  if (b == 1) {
    log_str ("Enable expanding UTF-8 characters in strings.\n");
    tl_set_expand_utf8 (1);
  } else if (b == 0) {
    log_str ("Disable expanding UTF-8 characters in strings.\n");
    tl_set_expand_utf8 (0);
  }
  return 0;
}