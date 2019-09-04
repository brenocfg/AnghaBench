#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  mrb; } ;
typedef  TYPE_1__ codegen_scope ;

/* Variables and functions */
 int /*<<< orphan*/  OP_ERR ; 
 int /*<<< orphan*/  genop_1 (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mrb_str_new_cstr (int /*<<< orphan*/ ,char const*) ; 
 int new_lit (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
raise_error(codegen_scope *s, const char *msg)
{
  int idx = new_lit(s, mrb_str_new_cstr(s->mrb, msg));

  genop_1(s, OP_ERR, idx);
}