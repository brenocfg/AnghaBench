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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  msg ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int mrb_int ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  E_RANGE_ERROR ; 
 int /*<<< orphan*/  FIXABLE (int) ; 
 unsigned int PACK_FLAG_LITTLEENDIAN ; 
 unsigned int PACK_FLAG_SIGNED ; 
 int /*<<< orphan*/  POSFIXABLE (int) ; 
 int /*<<< orphan*/  mrb_ary_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_fixnum_value (int) ; 
 int /*<<< orphan*/  mrb_raise (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned long) ; 

__attribute__((used)) static int
unpack_l(mrb_state *mrb, const unsigned char *src, int srclen, mrb_value ary, unsigned int flags)
{
#ifndef MRB_INT64
  char msg[60];
#endif
  uint32_t ul;
  mrb_int n;

  if (flags & PACK_FLAG_LITTLEENDIAN) {
    ul = (uint32_t)src[3] * 256*256*256;
    ul += (uint32_t)src[2] *256*256;
    ul += (uint32_t)src[1] *256;
    ul += (uint32_t)src[0];
  } else {
    ul = (uint32_t)src[0] * 256*256*256;
    ul += (uint32_t)src[1] *256*256;
    ul += (uint32_t)src[2] *256;
    ul += (uint32_t)src[3];
  }
  if (flags & PACK_FLAG_SIGNED) {
    int32_t sl = ul;
#ifndef MRB_INT64
    if (!FIXABLE(sl)) {
      snprintf(msg, sizeof(msg), "cannot unpack to Fixnum: %ld", (long)sl);
      mrb_raise(mrb, E_RANGE_ERROR, msg);
    }
#endif
    n = sl;
  } else {
#ifndef MRB_INT64
    if (!POSFIXABLE(ul)) {
      snprintf(msg, sizeof(msg), "cannot unpack to Fixnum: %lu", (unsigned long)ul);
      mrb_raise(mrb, E_RANGE_ERROR, msg);
    }
#endif
    n = ul;
  }
  mrb_ary_push(mrb, ary, mrb_fixnum_value(n));
  return 4;
}