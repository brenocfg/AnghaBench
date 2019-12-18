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
typedef  scalar_t__ uint16_t ;
struct TYPE_4__ {int /*<<< orphan*/ * iseq; } ;
typedef  TYPE_1__ mrb_irep ;
typedef  int /*<<< orphan*/  mrb_code ;
typedef  int /*<<< orphan*/  mrb_bool ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ mrb_debug_get_line (TYPE_1__*,int) ; 

__attribute__((used)) static mrb_bool
check_start_pc_for_line(mrb_irep *irep, mrb_code *pc, uint16_t line)
{
  if (pc > irep->iseq) {
    if (line == mrb_debug_get_line(irep, pc - irep->iseq - 1)) {
      return FALSE;
    }
  }
  return TRUE;
}