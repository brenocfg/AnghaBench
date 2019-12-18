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
struct TYPE_4__ {scalar_t__ sp; } ;
typedef  TYPE_1__ codegen_scope ;

/* Variables and functions */
 int /*<<< orphan*/  codegen_error (TYPE_1__*,char*) ; 

__attribute__((used)) static void
pop_n_(codegen_scope *s, int n)
{
  if ((int)s->sp-n < 0) {
    codegen_error(s, "stack pointer underflow");
  }
  s->sp-=n;
}