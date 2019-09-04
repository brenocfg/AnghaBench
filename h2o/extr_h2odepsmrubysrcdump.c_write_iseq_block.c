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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int ptrdiff_t ;
typedef  int /*<<< orphan*/  mrb_state ;
struct TYPE_3__ {int ilen; int /*<<< orphan*/  iseq; } ;
typedef  TYPE_1__ mrb_irep ;
typedef  int /*<<< orphan*/  mrb_code ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uint32_to_bin (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_padding (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ptrdiff_t
write_iseq_block(mrb_state *mrb, mrb_irep *irep, uint8_t *buf, uint8_t flags)
{
  uint8_t *cur = buf;

  cur += uint32_to_bin(irep->ilen, cur); /* number of opcode */
  cur += write_padding(cur);
  memcpy(cur, irep->iseq, irep->ilen * sizeof(mrb_code));
  cur += irep->ilen * sizeof(mrb_code);

  return cur - buf;
}