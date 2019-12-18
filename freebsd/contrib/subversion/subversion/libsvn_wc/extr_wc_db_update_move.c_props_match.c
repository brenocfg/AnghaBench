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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
struct TYPE_3__ {scalar_t__ nelts; } ;
typedef  TYPE_1__ apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  svn_prop_diffs (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
props_match(svn_boolean_t *match,
            apr_hash_t *src_props,
            apr_hash_t *dst_props,
            apr_pool_t *scratch_pool)
{
  if (!src_props && !dst_props)
    *match = TRUE;
  else if (!src_props || ! dst_props)
    *match = FALSE;
  else
    {
      apr_array_header_t *propdiffs;

      SVN_ERR(svn_prop_diffs(&propdiffs, src_props, dst_props, scratch_pool));
      *match = propdiffs->nelts ? FALSE : TRUE;
    }
  return SVN_NO_ERROR;
}