#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  mrb_sym ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  scalar_t__ mrb_int ;

/* Variables and functions */
 int MRB_DUMP_OK ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char const*,scalar_t__) ; 
 char* mrb_sym2name_len (int /*<<< orphan*/ *,int /*<<< orphan*/  const,scalar_t__*) ; 
 int /*<<< orphan*/  uint16_to_bin (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uint32_to_bin (size_t,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
write_lv_sym_table(mrb_state *mrb, uint8_t **start, mrb_sym const *syms, uint32_t syms_len)
{
  uint8_t *cur = *start;
  uint32_t i;
  const char *str;
  mrb_int str_len;

  cur += uint32_to_bin(syms_len, cur);

  for (i = 0; i < syms_len; ++i) {
    str = mrb_sym2name_len(mrb, syms[i], &str_len);
    cur += uint16_to_bin((uint16_t)str_len, cur);
    memcpy(cur, str, str_len);
    cur += str_len;
  }

  *start = cur;

  return MRB_DUMP_OK;
}