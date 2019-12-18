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
typedef  int mrb_bool ;
struct TYPE_4__ {scalar_t__ lastlabel; scalar_t__ pc; scalar_t__ lastpc; } ;
typedef  TYPE_1__ codegen_scope ;

/* Variables and functions */
 scalar_t__ no_optimize (TYPE_1__*) ; 

__attribute__((used)) static mrb_bool
no_peephole(codegen_scope *s)
{
  return no_optimize(s) || s->lastlabel == s->pc || s->pc == 0 || s->pc == s->lastpc;
}