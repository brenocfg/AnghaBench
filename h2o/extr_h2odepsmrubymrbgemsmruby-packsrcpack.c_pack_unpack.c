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
struct tmpl {int dummy; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  E_RUNTIME_ERROR ; 
#define  PACK_DIR_BASE64 137 
#define  PACK_DIR_CHAR 136 
#define  PACK_DIR_DOUBLE 135 
#define  PACK_DIR_FLOAT 134 
#define  PACK_DIR_HEX 133 
 int PACK_DIR_INVALID ; 
#define  PACK_DIR_LONG 132 
 int PACK_DIR_NUL ; 
#define  PACK_DIR_QUAD 131 
#define  PACK_DIR_SHORT 130 
#define  PACK_DIR_STR 129 
#define  PACK_DIR_UTF8 128 
 unsigned int PACK_FLAG_COUNT2 ; 
 int /*<<< orphan*/ * RARRAY_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ RSTRING_LEN (int /*<<< orphan*/ ) ; 
 scalar_t__ RSTRING_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ has_tmpl (struct tmpl*) ; 
 int /*<<< orphan*/  mrb_ary_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_ary_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 
 int /*<<< orphan*/  mrb_raise (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  prepare_tmpl (int /*<<< orphan*/ *,struct tmpl*) ; 
 int /*<<< orphan*/  read_tmpl (int /*<<< orphan*/ *,struct tmpl*,int*,int*,int*,int*,unsigned int*) ; 
 int unpack_a (int /*<<< orphan*/ *,unsigned char const*,int,int /*<<< orphan*/ ,int,unsigned int) ; 
 int unpack_c (int /*<<< orphan*/ *,unsigned char const*,int,int /*<<< orphan*/ ,unsigned int) ; 
 int unpack_double (int /*<<< orphan*/ *,unsigned char const*,int,int /*<<< orphan*/ ,unsigned int) ; 
 int unpack_float (int /*<<< orphan*/ *,unsigned char const*,int,int /*<<< orphan*/ ,unsigned int) ; 
 int unpack_h (int /*<<< orphan*/ *,unsigned char const*,int,int /*<<< orphan*/ ,int,unsigned int) ; 
 int unpack_l (int /*<<< orphan*/ *,unsigned char const*,int,int /*<<< orphan*/ ,unsigned int) ; 
 int unpack_m (int /*<<< orphan*/ *,unsigned char const*,int,int /*<<< orphan*/ ,unsigned int) ; 
 int unpack_q (int /*<<< orphan*/ *,unsigned char const*,int,int /*<<< orphan*/ ,unsigned int) ; 
 int unpack_s (int /*<<< orphan*/ *,unsigned char const*,int,int /*<<< orphan*/ ,unsigned int) ; 
 int unpack_utf8 (int /*<<< orphan*/ *,unsigned char const*,int,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ unpack_x (int /*<<< orphan*/ *,unsigned char const*,int,int /*<<< orphan*/ ,int,unsigned int) ; 

__attribute__((used)) static mrb_value
pack_unpack(mrb_state *mrb, mrb_value str, int single)
{
  mrb_value result;
  struct tmpl tmpl;
  int count;
  unsigned int flags;
  int dir, size, type;
  int srcidx, srclen;
  const unsigned char *sptr;

  prepare_tmpl(mrb, &tmpl);

  srcidx = 0;
  srclen = (int)RSTRING_LEN(str);

  result = mrb_ary_new(mrb);
  while (has_tmpl(&tmpl)) {
    read_tmpl(mrb, &tmpl, &dir, &type, &size, &count, &flags);

    if (dir == PACK_DIR_INVALID)
      continue;
    else if (dir == PACK_DIR_NUL) {
      srcidx += unpack_x(mrb, sptr, srclen - srcidx, result, count, flags);
      continue;
    }

    if (flags & PACK_FLAG_COUNT2) {
      sptr = (const unsigned char *)RSTRING_PTR(str) + srcidx;
      switch (dir) {
      case PACK_DIR_HEX:
        srcidx += unpack_h(mrb, sptr, srclen - srcidx, result, count, flags);
        break;
      case PACK_DIR_STR:
        srcidx += unpack_a(mrb, sptr, srclen - srcidx, result, count, flags);
        break;
      }
      continue;
    }

    while (count != 0) {
      if (srclen - srcidx < size) {
        while (count-- > 0) {
          mrb_ary_push(mrb, result, mrb_nil_value());
        }
        break;
      }

      sptr = (const unsigned char*)RSTRING_PTR(str) + srcidx;
      switch (dir) {
      case PACK_DIR_CHAR:
        srcidx += unpack_c(mrb, sptr, srclen - srcidx, result, flags);
        break;
      case PACK_DIR_SHORT:
        srcidx += unpack_s(mrb, sptr, srclen - srcidx, result, flags);
        break;
      case PACK_DIR_LONG:
        srcidx += unpack_l(mrb, sptr, srclen - srcidx, result, flags);
        break;
      case PACK_DIR_QUAD:
        srcidx += unpack_q(mrb, sptr, srclen - srcidx, result, flags);
        break;
      case PACK_DIR_BASE64:
        srcidx += unpack_m(mrb, sptr, srclen - srcidx, result, flags);
        break;
#ifndef MRB_WITHOUT_FLOAT
      case PACK_DIR_FLOAT:
        srcidx += unpack_float(mrb, sptr, srclen - srcidx, result, flags);
        break;
      case PACK_DIR_DOUBLE:
        srcidx += unpack_double(mrb, sptr, srclen - srcidx, result, flags);
        break;
#endif
      case PACK_DIR_UTF8:
        srcidx += unpack_utf8(mrb, sptr, srclen - srcidx, result, flags);
        break;
      default:
        mrb_raise(mrb, E_RUNTIME_ERROR, "mruby-pack's bug");
      }
      if (count > 0) {
        count--;
      }
    }
    if (single) break;
  }

  if (single) return RARRAY_PTR(result)[0];
  return result;
}