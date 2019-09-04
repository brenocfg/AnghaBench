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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  mrb_state ;
struct TYPE_3__ {int slen; scalar_t__* syms; } ;
typedef  TYPE_1__ mrb_irep ;
typedef  scalar_t__ mrb_int ;

/* Variables and functions */
 int /*<<< orphan*/  mrb_sym2name_len (int /*<<< orphan*/ *,scalar_t__,scalar_t__*) ; 

__attribute__((used)) static size_t
get_syms_block_size(mrb_state *mrb, mrb_irep *irep)
{
  size_t size = 0;
  int sym_no;
  mrb_int len;

  size += sizeof(uint32_t); /* slen */
  for (sym_no = 0; sym_no < irep->slen; sym_no++) {
    size += sizeof(uint16_t); /* snl(n) */
    if (irep->syms[sym_no] != 0) {
      mrb_sym2name_len(mrb, irep->syms[sym_no], &len);
      size += len + 1; /* sn(n) + null char */
    }
  }

  return size;
}