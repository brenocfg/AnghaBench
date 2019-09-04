#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tl_type {int constructors_num; } ;
struct tl_tree_type {struct tl_type* type; } ;
struct tl_combinator {int fIP_len; int var_num; scalar_t__ name; int args_num; void* fIP; TYPE_1__** args; scalar_t__ result; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int FLAG_OPT_VAR ; 
 void* IP_dup (void**,int) ; 
 scalar_t__ NAME_BOOL_FALSE ; 
 scalar_t__ NAME_BOOL_TRUE ; 
 scalar_t__ NAME_DOUBLE ; 
 scalar_t__ NAME_INT ; 
 scalar_t__ NAME_LONG ; 
 scalar_t__ NAME_MAYBE_FALSE ; 
 scalar_t__ NAME_MAYBE_TRUE ; 
 scalar_t__ NAME_STRING ; 
 scalar_t__ NAME_VECTOR ; 
 scalar_t__ NODE_TYPE_TYPE ; 
 scalar_t__ TYPE (scalar_t__) ; 
 int /*<<< orphan*/  assert (int) ; 
 int gen_field_fetch (TYPE_1__*,void**,int,int*,int,int) ; 
 int gen_uni (scalar_t__,void**,int,int*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 void* tlcomb_fetch_double ; 
 void* tlcomb_fetch_false ; 
 void* tlcomb_fetch_int ; 
 void* tlcomb_fetch_long ; 
 void* tlcomb_fetch_maybe ; 
 void* tlcomb_fetch_string ; 
 void* tlcomb_fetch_true ; 
 void* tlcomb_fetch_type ; 
 void* tlcomb_fetch_vector ; 
 void* tlsub_push_type_var ; 
 void* tlsub_ret_ok ; 

int gen_constructor_fetch (struct tl_combinator *c, void **IP, int max_size) {
  if (c->fIP) { return c->fIP_len; }
  if (max_size <= 10) { return -1; }
  int l = 0;
  assert (!c->fIP);
  int i;
  int vars[c->var_num];
  memset (vars, 0, sizeof (int) * c->var_num);
  int x = gen_uni (c->result, IP + l, max_size - l, vars);
  if (x < 0) { return -1; }
  l += x;
  if (c->name == NAME_INT) {
    IP[l ++] = tlcomb_fetch_int;
    IP[l ++] = tlsub_ret_ok;
    c->fIP = IP_dup (IP, l);
    c->fIP_len = l;
    return l;
  } else if (c->name == NAME_LONG) {
    IP[l ++] = tlcomb_fetch_long;
    IP[l ++] = tlsub_ret_ok;
    c->fIP = IP_dup (IP, l);
    c->fIP_len = l;
    return l;
  } else if (c->name == NAME_STRING) {
    IP[l ++] = tlcomb_fetch_string;
    IP[l ++] = tlsub_ret_ok;
    c->fIP = IP_dup (IP, l);
    c->fIP_len = l;
    return l;
  } else if (c->name == NAME_DOUBLE) {
    IP[l ++] = tlcomb_fetch_double;
    IP[l ++] = tlsub_ret_ok;
    c->fIP = IP_dup (IP, l);
    c->fIP_len = l;
    return l;
  } else if (c->name == NAME_VECTOR) {
    IP[l ++] = tlcomb_fetch_vector;
    static void *tIP[4];
    tIP[0] = tlsub_push_type_var;
    tIP[1] = (long)0;
    tIP[2] = tlcomb_fetch_type;
    tIP[3] = tlsub_ret_ok; 
    IP[l ++] = IP_dup (tIP, 4);
    IP[l ++] = tlsub_ret_ok;
    c->fIP = IP_dup (IP, l);
    c->fIP_len = l;
    return l;
  } else if (c->name == NAME_MAYBE_TRUE) {
    IP[l ++] = tlcomb_fetch_maybe;
    static void *tIP[4];
    tIP[0] = tlsub_push_type_var;
    tIP[1] = (long)0;
    tIP[2] = tlcomb_fetch_type;
    tIP[3] = tlsub_ret_ok; 
    IP[l ++] = IP_dup (tIP, 4);
    IP[l ++] = tlsub_ret_ok;
    c->fIP = IP_dup (IP, l);
    c->fIP_len = l;
    return l;
  } else if (c->name == NAME_MAYBE_FALSE || c->name == NAME_BOOL_FALSE) {
    IP[l ++] = tlcomb_fetch_false;
    IP[l ++] = tlsub_ret_ok;
    c->fIP = IP_dup (IP, l);
    c->fIP_len = l;
    return l;
  } else if (c->name == NAME_BOOL_TRUE) {
    IP[l ++] = tlcomb_fetch_true;
    IP[l ++] = tlsub_ret_ok;
    c->fIP = IP_dup (IP, l);
    c->fIP_len = l;
    return l;
  }

  if (TYPE (c->result) == NODE_TYPE_TYPE) {
    struct tl_type *t = ((struct tl_tree_type *)(c->result))->type;
    if (t->constructors_num == 1) {
      int x = -1;
      int z = 0;
      for (i = 0; i < c->args_num; i++) if (!(c->args[i]->flags & FLAG_OPT_VAR)) {
        z ++;
        x = i;
      }
      if (z == 1) { 
        x = gen_field_fetch (c->args[x], IP + l, max_size - l, vars, x + 1, 1);
        if (x < 0) { return -1; }
        l += x;
        if (max_size - l <= 10) { return -1; }
        IP[l ++] = tlsub_ret_ok;
        c->fIP = IP_dup (IP, l);
        c->fIP_len = l;
        return l;
      }
    }
  }
  for (i = 0; i < c->args_num; i++) if (!(c->args[i]->flags & FLAG_OPT_VAR)) {
    x = gen_field_fetch (c->args[i], IP + l, max_size - l, vars, i + 1, 0);
    if (x < 0) { return -1; }
    l += x;
//    fprintf (stderr, ".");
  }
  if (max_size - l <= 10) { return -1; }
  IP[l ++] = tlsub_ret_ok;
  c->fIP = IP_dup (IP, l);
  c->fIP_len = l;
  return l;
}