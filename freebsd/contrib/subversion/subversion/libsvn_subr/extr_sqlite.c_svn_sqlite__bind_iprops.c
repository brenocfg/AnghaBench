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
struct TYPE_3__ {int /*<<< orphan*/  len; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_sqlite__stmt_t ;
typedef  int /*<<< orphan*/  svn_skel_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 TYPE_1__* svn_skel__unparse (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_skel__unparse_iproplist (int /*<<< orphan*/ **,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__bind_blob (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

svn_error_t *
svn_sqlite__bind_iprops(svn_sqlite__stmt_t *stmt,
                        int slot,
                        const apr_array_header_t *inherited_props,
                        apr_pool_t *scratch_pool)
{
  svn_skel_t *skel;
  svn_stringbuf_t *properties;

  if (inherited_props == NULL)
    return svn_error_trace(svn_sqlite__bind_blob(stmt, slot, NULL, 0));

  SVN_ERR(svn_skel__unparse_iproplist(&skel, inherited_props,
                                      scratch_pool, scratch_pool));
  properties = svn_skel__unparse(skel, scratch_pool);
  return svn_error_trace(svn_sqlite__bind_blob(stmt,
                                               slot,
                                               properties->data,
                                               properties->len));
}