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
typedef  int /*<<< orphan*/  svn_stringbuf_t ;

/* Variables and functions */
 char const* _ (char*) ; 
 int /*<<< orphan*/  svn_stringbuf_appendcstr (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static void append_reason(svn_stringbuf_t *errmsg, const char *reason, int *reasons)
{
  if (*reasons < 1)
    svn_stringbuf_appendcstr(errmsg, _(": "));
  else
    svn_stringbuf_appendcstr(errmsg, _(", "));
  svn_stringbuf_appendcstr(errmsg, reason);
  (*reasons)++;
}