#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ message; } ;
typedef  TYPE_1__ svn_error_t ;
typedef  int svn_boolean_t ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  error_tracing_link ; 
 int /*<<< orphan*/  strcmp (scalar_t__,int /*<<< orphan*/ ) ; 

svn_boolean_t
svn_error__is_tracing_link(const svn_error_t *err)
{
#ifdef SVN_ERR__TRACING
  /* ### A strcmp()?  Really?  I think it's the best we can do unless
     ### we add a boolean field to svn_error_t that's set only for
     ### these "placeholder error chain" items.  Not such a bad idea,
     ### really...  */
  return (err && err->message && !strcmp(err->message, error_tracing_link));
#else
  return FALSE;
#endif
}