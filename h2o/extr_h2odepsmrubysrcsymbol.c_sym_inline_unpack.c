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
typedef  int mrb_sym ;

/* Variables and functions */
 int /*<<< orphan*/  mrb_assert (int) ; 
 char const* sym_inline_unpack_with_bit (int,char*,int) ; 

__attribute__((used)) static const char*
sym_inline_unpack(mrb_sym sym, char *buf)
{
  mrb_assert(sym&1);

  if (sym&2) {                  /* all lower case (5bits/char) */
    return sym_inline_unpack_with_bit(sym, buf, 5);
  }
  return sym_inline_unpack_with_bit(sym, buf, 6);
}