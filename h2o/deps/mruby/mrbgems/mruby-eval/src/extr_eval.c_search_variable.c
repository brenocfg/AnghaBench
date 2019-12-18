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
typedef  int uint16_t ;
typedef  scalar_t__ mrb_sym ;
typedef  int /*<<< orphan*/  mrb_state ;
struct TYPE_5__ {int nlocals; TYPE_1__* lv; } ;
typedef  TYPE_2__ mrb_irep ;
struct TYPE_4__ {scalar_t__ name; } ;

/* Variables and functions */
 TYPE_2__* get_closure_irep (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static uint16_t
search_variable(mrb_state *mrb, mrb_sym vsym, int bnest)
{
  mrb_irep *virep;
  int level;
  int pos;

  for (level = 0; (virep = get_closure_irep(mrb, level)); level++) {
    if (virep->lv == NULL) {
      continue;
    }
    for (pos = 0; pos < virep->nlocals - 1; pos++) {
      if (vsym == virep->lv[pos].name) {
        return (pos+1)<<8 | (level+bnest);
      }
    }
  }

  return 0;
}