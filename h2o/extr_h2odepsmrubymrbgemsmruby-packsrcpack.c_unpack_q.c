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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  msg ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int mrb_int ;
typedef  int int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  E_RANGE_ERROR ; 
 int /*<<< orphan*/  FIXABLE (int) ; 
 unsigned int PACK_FLAG_LITTLEENDIAN ; 
 unsigned int PACK_FLAG_SIGNED ; 
 int /*<<< orphan*/  POSFIXABLE (int) ; 
 int /*<<< orphan*/  mrb_ary_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_fixnum_value (int) ; 
 int /*<<< orphan*/  mrb_raise (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned long long) ; 

__attribute__((used)) static int
unpack_q(mrb_state *mrb, const unsigned char *src, int srclen, mrb_value ary, unsigned int flags)
{
  char msg[60];
  uint64_t ull;
  int i, pos, step;
  mrb_int n;

  if (flags & PACK_FLAG_LITTLEENDIAN) {
    pos  = 7;
    step = -1;
  } else {
    pos  = 0;
    step = 1;
  }
  ull = 0;
  for (i = 0; i < 8; i++) {
    ull = ull * 256 + (uint64_t)src[pos];
    pos += step;
  }
  if (flags & PACK_FLAG_SIGNED) {
    int64_t sll = ull;
    if (!FIXABLE(sll)) {
      snprintf(msg, sizeof(msg), "cannot unpack to Fixnum: %lld", (long long)sll);
      mrb_raise(mrb, E_RANGE_ERROR, msg);
    }
    n = sll;
  } else {
    if (!POSFIXABLE(ull)) {
      snprintf(msg, sizeof(msg), "cannot unpack to Fixnum: %llu", (unsigned long long)ull);
      mrb_raise(mrb, E_RANGE_ERROR, msg);
    }
    n = ull;
  }
  mrb_ary_push(mrb, ary, mrb_fixnum_value(n));
  return 8;
}