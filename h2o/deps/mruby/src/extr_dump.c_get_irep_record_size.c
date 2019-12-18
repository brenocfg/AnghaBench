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
typedef  int /*<<< orphan*/  mrb_state ;
struct TYPE_4__ {int rlen; struct TYPE_4__** reps; } ;
typedef  TYPE_1__ mrb_irep ;

/* Variables and functions */
 size_t get_irep_record_size_1 (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static size_t
get_irep_record_size(mrb_state *mrb, mrb_irep *irep)
{
  size_t size = 0;
  int irep_no;

  size = get_irep_record_size_1(mrb, irep);
  for (irep_no = 0; irep_no < irep->rlen; irep_no++) {
    size += get_irep_record_size(mrb, irep->reps[irep_no]);
  }
  return size;
}