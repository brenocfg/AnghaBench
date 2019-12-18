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
struct re_pattern_buffer {int no_sub; int newline_anchor; } ;
typedef  scalar_t__ reg_errcode_t ;

/* Variables and functions */
 int RE_NO_SUB ; 
 scalar_t__ __re_error_msgid ; 
 scalar_t__* __re_error_msgid_idx ; 
 char const* gettext (scalar_t__) ; 
 scalar_t__ re_compile_internal (struct re_pattern_buffer*,char const*,size_t,int) ; 
 int re_syntax_options ; 

const char *
re_compile_pattern (const char *pattern,
		    size_t length,
		    struct re_pattern_buffer *bufp)
{
  reg_errcode_t ret;

  /* And GNU code determines whether or not to get register information
     by passing null for the REGS argument to re_match, etc., not by
     setting no_sub, unless RE_NO_SUB is set.  */
  bufp->no_sub = !!(re_syntax_options & RE_NO_SUB);

  /* Match anchors at newline.  */
  bufp->newline_anchor = 1;

  ret = re_compile_internal (bufp, pattern, length, re_syntax_options);

  if (!ret)
    return NULL;
  return gettext (__re_error_msgid + __re_error_msgid_idx[(int) ret]);
}