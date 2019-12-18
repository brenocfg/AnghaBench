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
typedef  int /*<<< orphan*/  va_list ;
struct state {size_t sz; unsigned char* str; unsigned char* s; unsigned char* theend; int /*<<< orphan*/  reserve; int /*<<< orphan*/  append_char; scalar_t__ max_sz; } ;

/* Variables and functions */
 int /*<<< orphan*/  sn_append_char ; 
 int /*<<< orphan*/  sn_reserve ; 
 int xyzprintf (struct state*,char const*,int /*<<< orphan*/ ) ; 

int
vsnprintf (char *str, size_t sz, const char *format, va_list args)
{
  struct state state;
  int ret;
  unsigned char *ustr = (unsigned char *)str;

  state.max_sz = 0;
  state.sz     = sz;
  state.str    = ustr;
  state.s      = ustr;
  state.theend = ustr + sz - 1;
  state.append_char = sn_append_char;
  state.reserve     = sn_reserve;

  ret = xyzprintf (&state, format, args);
  *state.s = '\0';
  if (ret)
    return sz;
  else
    return state.s - state.str;
}