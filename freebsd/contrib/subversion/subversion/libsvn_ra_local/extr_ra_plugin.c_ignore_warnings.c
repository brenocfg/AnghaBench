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
struct TYPE_3__ {int /*<<< orphan*/  apr_err; } ;
typedef  TYPE_1__ svn_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_DBG (char*) ; 
 int /*<<< orphan*/  svn_error_symbolic_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ignore_warnings(void *baton,
                svn_error_t *err)
{
#ifdef SVN_DEBUG
  SVN_DBG(("Ignoring FS warning %s\n",
           svn_error_symbolic_name(err ? err->apr_err : 0)));
#endif
  return;
}