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
struct tl_combinator {int var_num; int args_num; int IP_len; int /*<<< orphan*/  IP; int /*<<< orphan*/  result; TYPE_1__** args; scalar_t__ name; } ;
struct TYPE_3__ {int flags; } ;

/* Variables and functions */
 int FLAG_EXCL ; 
 int FLAG_OPT_VAR ; 
 int /*<<< orphan*/  IP_dup (void**,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int gen_create (int /*<<< orphan*/ ,void**,int,int*) ; 
 int gen_field (TYPE_1__*,void**,int,int*,int,int /*<<< orphan*/ ) ; 
 int gen_field_excl (TYPE_1__*,void**,int,int*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 void* tls_store_int ; 
 void* tlsub_ret ; 

int gen_function_store (struct tl_combinator *c, void **IP, int max_size) {
  if (max_size <= 10) { return -1; }
  assert (!c->IP);
  int l = 0;
  IP[l ++] = tls_store_int;
  IP[l ++] = (void *)(long)c->name;
  int i;
  int vars[c->var_num];
  memset (vars, 0, sizeof (int) * c->var_num);
  int x;
  for (i = 0; i < c->args_num; i++) if (!(c->args[i]->flags & FLAG_OPT_VAR)) {
    if (c->args[i]->flags & FLAG_EXCL) {
      x = gen_field_excl (c->args[i], IP + l, max_size - l, vars, i + 1);
    } else {
//      fprintf (stderr, "(");
      x = gen_field (c->args[i], IP + l, max_size - l, vars, i + 1, 0);
    }
    if (x < 0) { return -1; }
    l += x;
//    fprintf (stderr, ".");
  }
  int r = gen_create (c->result, IP + l, max_size - l, vars);
  if (r < 0) { return -1; }
  l += r;
  if (max_size - l <= 10) { return -1; }
  IP[l ++] = tlsub_ret;
  c->IP = IP_dup (IP, l);
  c->IP_len = l;
  return l;
}