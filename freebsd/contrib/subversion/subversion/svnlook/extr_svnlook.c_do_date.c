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
typedef  int /*<<< orphan*/  svnlook_ctxt_t ;
struct TYPE_3__ {scalar_t__ data; } ;
typedef  TYPE_1__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_time_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_REVISION_DATE ; 
 int /*<<< orphan*/  get_property (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_cmdline_printf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  svn_time_from_cstring (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 char* svn_time_to_human_cstring (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
do_date(svnlook_ctxt_t *c, apr_pool_t *pool)
{
  svn_string_t *prop_value;

  SVN_ERR(get_property(&prop_value, c, SVN_PROP_REVISION_DATE, pool));
  if (prop_value && prop_value->data)
    {
      /* Convert the date for humans. */
      apr_time_t aprtime;
      const char *time_utf8;

      SVN_ERR(svn_time_from_cstring(&aprtime, prop_value->data, pool));

      time_utf8 = svn_time_to_human_cstring(aprtime, pool);

      SVN_ERR(svn_cmdline_printf(pool, "%s", time_utf8));
    }

  SVN_ERR(svn_cmdline_printf(pool, "\n"));
  return SVN_NO_ERROR;
}