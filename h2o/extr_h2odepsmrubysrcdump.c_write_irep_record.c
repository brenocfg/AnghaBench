#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  mrb_state ;
struct TYPE_8__ {int rlen; struct TYPE_8__** reps; } ;
typedef  TYPE_1__ mrb_irep ;

/* Variables and functions */
 int MRB_DUMP_GENERAL_FAILURE ; 
 int MRB_DUMP_INVALID_IREP ; 
 int MRB_DUMP_OK ; 
 size_t get_irep_record_size_1 (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  write_irep_header (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_iseq_block (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_pool_block (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_syms_block (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
write_irep_record(mrb_state *mrb, mrb_irep *irep, uint8_t *bin, size_t *irep_record_size, uint8_t flags)
{
  int i;
  uint8_t *src = bin;

  if (irep == NULL) {
    return MRB_DUMP_INVALID_IREP;
  }

  *irep_record_size = get_irep_record_size_1(mrb, irep);
  if (*irep_record_size == 0) {
    return MRB_DUMP_GENERAL_FAILURE;
  }

  bin += write_irep_header(mrb, irep, bin);
  bin += write_iseq_block(mrb, irep, bin, flags);
  bin += write_pool_block(mrb, irep, bin);
  bin += write_syms_block(mrb, irep, bin);

  for (i = 0; i < irep->rlen; i++) {
    int result;
    size_t rsize;

    result = write_irep_record(mrb, irep->reps[i], bin, &rsize, flags);
    if (result != MRB_DUMP_OK) {
      return result;
    }
    bin += rsize;
  }
  *irep_record_size = bin - src;
  return MRB_DUMP_OK;
}