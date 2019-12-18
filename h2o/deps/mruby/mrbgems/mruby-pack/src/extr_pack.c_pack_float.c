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
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int mrb_int ;

/* Variables and functions */
 unsigned int PACK_FLAG_LITTLEENDIAN ; 
 int /*<<< orphan*/ * RSTRING_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ littleendian ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ mrb_float (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  str_len_ensure (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
pack_float(mrb_state *mrb, mrb_value o, mrb_value str, mrb_int sidx, unsigned int flags)
{
  int i;
  float f;
  uint8_t *buffer = (uint8_t *)&f;
  str = str_len_ensure(mrb, str, sidx + 4);
  f = (float)mrb_float(o);

  if (flags & PACK_FLAG_LITTLEENDIAN) {
    if (littleendian) {
      memcpy(RSTRING_PTR(str) + sidx, buffer, 4);
    }
    else {
      for (i = 0; i < 4; ++i) {
        RSTRING_PTR(str)[sidx + i] = buffer[4 - i - 1];
      }
    }
  } else {
    if (littleendian) {
      for (i = 0; i < 4; ++i) {
        RSTRING_PTR(str)[sidx + i] = buffer[4 - i - 1];
      }
    }
    else {
      memcpy(RSTRING_PTR(str) + sidx, buffer, 4);
    }
  }

  return 4;
}