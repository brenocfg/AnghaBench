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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  mrb_state ;
struct TYPE_3__ {int nlocals; int rlen; struct TYPE_3__** reps; } ;
typedef  TYPE_1__ mrb_irep ;

/* Variables and functions */

__attribute__((used)) static size_t
get_lv_record_size(mrb_state *mrb, mrb_irep *irep)
{
  size_t ret = 0;
  int i;

  ret += (sizeof(uint16_t) + sizeof(uint16_t)) * (irep->nlocals - 1);

  for (i = 0; i < irep->rlen; ++i) {
    ret += get_lv_record_size(mrb, irep->reps[i]);
  }

  return ret;
}