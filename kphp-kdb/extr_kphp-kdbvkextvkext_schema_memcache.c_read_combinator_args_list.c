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
struct tl_combinator {int args_num; char* id; scalar_t__ var_num; int /*<<< orphan*/  args; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_PMALLOC (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int) ; 
 int read_args_list (int /*<<< orphan*/ ,int,scalar_t__*) ; 
 int /*<<< orphan*/  stderr ; 
 int tl_parse_int () ; 
 int verbosity ; 
 int /*<<< orphan*/  zzmalloc0 (int) ; 

int read_combinator_args_list (struct tl_combinator *c) {
  c->args_num = tl_parse_int ();
  if (verbosity >= 2) {
    fprintf (stderr, "c->id = %s, c->args_num = %d\n", c->id, c->args_num);
  }
  if (c->args_num < 0 || c->args_num > 1000) {
    return -1;
  }
  c->args = zzmalloc0 (sizeof (void *) * c->args_num);
  c->var_num = 0;
  ADD_PMALLOC (sizeof (void *) * c->args_num);
  return read_args_list (c->args, c->args_num, &c->var_num);
}