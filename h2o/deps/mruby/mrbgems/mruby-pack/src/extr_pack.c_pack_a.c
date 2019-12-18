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
typedef  long mrb_int ;

/* Variables and functions */
 unsigned int PACK_FLAG_Z ; 
 unsigned int PACK_FLAG_a ; 
 long RSTRING_LEN (int /*<<< orphan*/ ) ; 
 char* RSTRING_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char*,long) ; 
 int /*<<< orphan*/  str_len_ensure (int /*<<< orphan*/ *,int /*<<< orphan*/ ,long) ; 

__attribute__((used)) static int
pack_a(mrb_state *mrb, mrb_value src, mrb_value dst, mrb_int didx, long count, unsigned int flags)
{
  mrb_int copylen, slen, padlen;
  char *dptr, *dptr0, pad, *sptr;

  sptr = RSTRING_PTR(src);
  slen = RSTRING_LEN(src);

  if ((flags & PACK_FLAG_a) || (flags & PACK_FLAG_Z))
    pad = '\0';
  else
    pad = ' ';

  if (count == 0) {
    return 0;
  } else if (count == -1) {
    copylen = slen;
    padlen = (flags & PACK_FLAG_Z) ? 1 : 0;
  } else if (count < slen) {
    copylen = count;
    padlen = 0;
  } else {
    copylen = slen;
    padlen = count - slen;
  }

  dst = str_len_ensure(mrb, dst, didx + copylen + padlen);
  dptr0 = dptr = RSTRING_PTR(dst) + didx;
  memcpy(dptr, sptr, copylen);
  dptr += copylen;
  while (padlen-- > 0) {
    *dptr++ = pad;
  }

  return (int)(dptr - dptr0);
}