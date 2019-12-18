#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_client_ctx_t ;
typedef  int /*<<< orphan*/  svn_client_conflict_t ;
struct TYPE_6__ {char const* propname; } ;
struct TYPE_7__ {TYPE_1__ prop; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* do_resolve_func ) (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;TYPE_2__ type_data; } ;
typedef  TYPE_3__ svn_client_conflict_option_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  assert_prop_conflict (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_client_conflict_prop_resolve(svn_client_conflict_t *conflict,
                                 const char *propname,
                                 svn_client_conflict_option_t *option,
                                 svn_client_ctx_t *ctx,
                                 apr_pool_t *scratch_pool)
{
  SVN_ERR(assert_prop_conflict(conflict, scratch_pool));
  option->type_data.prop.propname = propname;
  SVN_ERR(option->do_resolve_func(option, conflict, ctx, scratch_pool));

  return SVN_NO_ERROR;
}