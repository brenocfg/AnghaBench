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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int mrb_int ;

/* Variables and functions */
 unsigned int PACK_FLAG_LITTLEENDIAN ; 
 int* RSTRING_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ mrb_fixnum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  str_len_ensure (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
pack_s(mrb_state *mrb, mrb_value o, mrb_value str, mrb_int sidx, unsigned int flags)
{
  uint16_t n;

  str = str_len_ensure(mrb, str, sidx + 2);
  n = (uint16_t)mrb_fixnum(o);
  if (flags & PACK_FLAG_LITTLEENDIAN) {
    RSTRING_PTR(str)[sidx+0] = n % 256;
    RSTRING_PTR(str)[sidx+1] = n / 256;
  } else {
    RSTRING_PTR(str)[sidx+0] = n / 256;
    RSTRING_PTR(str)[sidx+1] = n % 256;
  }
  return 2;
}