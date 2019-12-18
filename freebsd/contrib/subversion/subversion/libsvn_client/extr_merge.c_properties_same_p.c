#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
struct TYPE_5__ {int nelts; } ;
typedef  TYPE_1__ apr_array_header_t ;
struct TYPE_6__ {char* name; } ;

/* Variables and functions */
 TYPE_3__ APR_ARRAY_IDX (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_MERGEINFO ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_prop_diffs (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_prop_t ; 
 scalar_t__ svn_wc_is_normal_prop (char const*) ; 

__attribute__((used)) static svn_error_t *
properties_same_p(svn_boolean_t *same,
                  apr_hash_t *props1,
                  apr_hash_t *props2,
                  apr_pool_t *scratch_pool)
{
  apr_array_header_t *prop_changes;
  int i, diffs;

  /* Examine the properties that differ */
  SVN_ERR(svn_prop_diffs(&prop_changes, props1, props2, scratch_pool));
  diffs = 0;
  for (i = 0; i < prop_changes->nelts; i++)
    {
      const char *pname = APR_ARRAY_IDX(prop_changes, i, svn_prop_t).name;

      /* Count the properties we're interested in; ignore the rest */
      if (svn_wc_is_normal_prop(pname)
          && strcmp(pname, SVN_PROP_MERGEINFO) != 0)
        diffs++;
    }
  *same = (diffs == 0);
  return SVN_NO_ERROR;
}