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
struct TYPE_3__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_hash_pool_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_pstrmemdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_dirent_get_absolute (char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
add_externals(apr_hash_t *externals,
              const char *path,
              const svn_string_t *externals_prop_val)
{
  apr_pool_t *pool = apr_hash_pool_get(externals);
  const char *local_abspath;

  if (! externals_prop_val)
    return SVN_NO_ERROR;

  SVN_ERR(svn_dirent_get_absolute(&local_abspath, path, pool));

  svn_hash_sets(externals, local_abspath,
                apr_pstrmemdup(pool, externals_prop_val->data,
                               externals_prop_val->len));

  return SVN_NO_ERROR;
}