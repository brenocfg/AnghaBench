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
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 unsigned int PACK_FLAG_SIGNED ; 
 int /*<<< orphan*/  mrb_ary_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_fixnum_value (unsigned char) ; 

__attribute__((used)) static int
unpack_c(mrb_state *mrb, const void *src, int srclen, mrb_value ary, unsigned int flags)
{
  if (flags & PACK_FLAG_SIGNED)
    mrb_ary_push(mrb, ary, mrb_fixnum_value(*(signed char *)src));
  else
    mrb_ary_push(mrb, ary, mrb_fixnum_value(*(unsigned char *)src));
  return 1;
}