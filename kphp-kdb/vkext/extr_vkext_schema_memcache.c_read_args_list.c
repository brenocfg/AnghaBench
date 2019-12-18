#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct arg {int exist_var_num; int flags; int var_num; TYPE_1__* type; void* exist_var_bit; int /*<<< orphan*/  id; } ;
struct TYPE_4__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_MALLOC (int) ; 
 int /*<<< orphan*/  ADD_PMALLOC (int) ; 
 int FLAG_NOVAR ; 
 int FLAG_OPT_FIELD ; 
 void* TLS_ARG ; 
 void* TLS_ARG_V2 ; 
 scalar_t__ TL_IS_NAT_VAR (TYPE_1__*) ; 
 TYPE_1__* read_tree (int*) ; 
 TYPE_1__* read_type_expr (int*) ; 
 int schema_version ; 
 int strlen (int /*<<< orphan*/ ) ; 
 void* tl_parse_int () ; 
 scalar_t__ tl_parse_string (int /*<<< orphan*/ *) ; 
 struct arg* zzmalloc0 (int) ; 

int read_args_list (struct arg **args, int args_num, int *var_num) {
  int i;
  for (i = 0; i < args_num; i++) {
    args[i] = zzmalloc0 (sizeof (struct arg));
    args[i]->exist_var_num = -1;
    args[i]->exist_var_bit = 0;
    ADD_PMALLOC (sizeof (struct arg));
    if (schema_version == 1) {
      if (tl_parse_int () != TLS_ARG) {
        return -1;
      }
    } else {
      if (tl_parse_int () != TLS_ARG_V2) {
        return -1;
      }
    }
    if (tl_parse_string (&args[i]->id) < 0) {
      return -1;
    }
    ADD_MALLOC (strlen (args[i]->id));
    ADD_PMALLOC (strlen (args[i]->id));
    args[i]->flags = tl_parse_int ();
    if (schema_version >= 2) {
      if (args[i]->flags & 2) {
        args[i]->flags &= ~2;
        args[i]->flags |= (1 << 20);
      }
      if (args[i]->flags & 4) {
        args[i]->flags &= ~4;
        args[i]->var_num = tl_parse_int ();
      } else {
        args[i]->var_num = -1;
      }
    } else {
      args[i]->var_num = tl_parse_int ();
    }
    if (args[i]->var_num >= *var_num) {
      *var_num = args[i]->var_num + 1;
    }
    if (args[i]->flags & FLAG_OPT_FIELD) {
      args[i]->exist_var_num = tl_parse_int ();
      args[i]->exist_var_bit = tl_parse_int ();
    }
    if (schema_version >= 2) {
      args[i]->type = read_type_expr (var_num);
    } else {
      args[i]->type = read_tree (var_num);
    }
    if (!args[i]->type) {
      return -1;
    }
    if (args[i]->var_num < 0 && args[i]->exist_var_num < 0 && (TL_IS_NAT_VAR(args[i]->type) || (args[i]->type->flags & FLAG_NOVAR))) {
      args[i]->flags |= FLAG_NOVAR;
    }
  }
  return 1;
}