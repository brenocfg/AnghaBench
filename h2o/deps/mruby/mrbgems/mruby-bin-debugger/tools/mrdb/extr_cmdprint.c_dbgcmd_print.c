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
typedef  size_t uint8_t ;
struct TYPE_3__ {int wcnt; int print_no; int /*<<< orphan*/  dbg; int /*<<< orphan*/ * words; } ;
typedef  TYPE_1__ mrdb_state ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int /*<<< orphan*/  dbgcmd_state ;

/* Variables and functions */
 int /*<<< orphan*/  DBGST_PROMPT ; 
 int /*<<< orphan*/  RSTRING_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RSTRING_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_debug_eval (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_gc_arena_restore (int /*<<< orphan*/ *,int) ; 
 int mrb_gc_arena_save (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_str_cat_cstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_str_cat_lit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mrb_str_new_cstr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  puts (char*) ; 

dbgcmd_state
dbgcmd_print(mrb_state *mrb, mrdb_state *mrdb)
{
  mrb_value expr;
  mrb_value result;
  mrb_value s;
  uint8_t wcnt;
  int ai;

  if (mrdb->wcnt <= 1) {
    puts("Parameter not specified.");
    return DBGST_PROMPT;
  }

  ai = mrb_gc_arena_save(mrb);

  /* eval expr */
  expr = mrb_str_new_cstr(mrb, NULL);
  for (wcnt=1; wcnt<mrdb->wcnt; wcnt++) {
    expr = mrb_str_cat_lit(mrb, expr, " ");
    expr = mrb_str_cat_cstr(mrb, expr, mrdb->words[wcnt]);
  }

  result = mrb_debug_eval(mrb, mrdb->dbg, RSTRING_PTR(expr), RSTRING_LEN(expr), NULL);

  /* $print_no = result */
  s = mrb_str_cat_lit(mrb, result, "\0");
  printf("$%lu = %s\n", (unsigned long)mrdb->print_no++, RSTRING_PTR(s));

  if (mrdb->print_no == 0) {
    mrdb->print_no = 1;
  }

  mrb_gc_arena_restore(mrb, ai);

  return DBGST_PROMPT;
}