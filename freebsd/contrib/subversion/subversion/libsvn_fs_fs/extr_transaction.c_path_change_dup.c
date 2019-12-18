#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ copyfrom_path; int /*<<< orphan*/  node_rev_id; } ;
typedef  TYPE_1__ svn_fs_path_change2_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 TYPE_1__* apr_pmemdup (int /*<<< orphan*/ *,TYPE_1__ const*,int) ; 
 scalar_t__ apr_pstrdup (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  svn_fs_fs__id_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_fs_path_change2_t *
path_change_dup(const svn_fs_path_change2_t *source,
                apr_pool_t *result_pool)
{
  svn_fs_path_change2_t *result = apr_pmemdup(result_pool, source,
                                              sizeof(*source));
  result->node_rev_id = svn_fs_fs__id_copy(source->node_rev_id, result_pool);
  if (source->copyfrom_path)
    result->copyfrom_path = apr_pstrdup(result_pool, source->copyfrom_path);

  return result;
}