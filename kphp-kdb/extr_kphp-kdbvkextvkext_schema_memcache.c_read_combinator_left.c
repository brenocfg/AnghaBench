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
struct tl_combinator {scalar_t__ args; scalar_t__ var_num; scalar_t__ args_num; } ;

/* Variables and functions */
 int TLS_COMBINATOR_LEFT ; 
 int TLS_COMBINATOR_LEFT_BUILTIN ; 
 int read_combinator_args_list (struct tl_combinator*) ; 
 scalar_t__ tl_parse_error () ; 
 int tl_parse_int () ; 

int read_combinator_left (struct tl_combinator *c) {
  
  int x = tl_parse_int ();
  if (tl_parse_error ()) {
    return -1;
  }

  if (x == TLS_COMBINATOR_LEFT_BUILTIN) {
    c->args_num = 0;
    c->var_num = 0;
    c->args = 0;
    return 1;
  } else if (x == TLS_COMBINATOR_LEFT) {
    return read_combinator_args_list (c);
  } else {
    return -1;
  }
}