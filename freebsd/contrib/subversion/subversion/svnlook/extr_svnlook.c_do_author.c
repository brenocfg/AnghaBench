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
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_REVISION_AUTHOR ; 
 int /*<<< orphan*/  get_property (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_cmdline_printf (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static svn_error_t *
do_author(svnlook_ctxt_t *c, apr_pool_t *pool)
{
  svn_string_t *prop_value;

  SVN_ERR(get_property(&prop_value, c,
                       SVN_PROP_REVISION_AUTHOR, pool));
  if (prop_value && prop_value->data)
    SVN_ERR(svn_cmdline_printf(pool, "%s", prop_value->data));

  SVN_ERR(svn_cmdline_printf(pool, "\n"));
  return SVN_NO_ERROR;
}