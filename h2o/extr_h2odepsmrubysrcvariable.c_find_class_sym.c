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
struct csym_arg {scalar_t__ sym; struct RClass* c; } ;
struct RClass {int /*<<< orphan*/  iv; } ;
typedef  scalar_t__ mrb_sym ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  csym_i ; 
 int /*<<< orphan*/  iv_foreach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct csym_arg*) ; 

__attribute__((used)) static mrb_sym
find_class_sym(mrb_state *mrb, struct RClass *outer, struct RClass *c)
{
  struct csym_arg arg;

  if (!outer) return 0;
  if (outer == c) return 0;
  arg.c = c;
  arg.sym = 0;
  iv_foreach(mrb, outer->iv, csym_i, &arg);
  return arg.sym;
}