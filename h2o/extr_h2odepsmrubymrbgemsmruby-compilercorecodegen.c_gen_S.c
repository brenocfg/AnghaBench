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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_4__ {int pc; } ;
typedef  TYPE_1__ codegen_scope ;

/* Variables and functions */
 int /*<<< orphan*/  emit_S (TYPE_1__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
gen_S(codegen_scope *s, uint16_t i)
{
  emit_S(s, s->pc, i);
  s->pc += 2;
}