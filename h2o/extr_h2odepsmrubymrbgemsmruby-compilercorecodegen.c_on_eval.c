#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mrb_bool ;
struct TYPE_5__ {TYPE_1__* parser; } ;
typedef  TYPE_2__ codegen_scope ;
struct TYPE_4__ {scalar_t__ on_eval; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static
mrb_bool
on_eval(codegen_scope *s)
{
  if (s && s->parser && s->parser->on_eval)
    return TRUE;
  return FALSE;
}