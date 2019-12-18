#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct TYPE_8__ {scalar_t__ copyfrom_path; TYPE_1__ path; } ;
typedef  TYPE_2__ svn_fs_x__change_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 TYPE_2__* apr_pmemdup (int /*<<< orphan*/ *,TYPE_2__ const*,int) ; 
 scalar_t__ apr_pstrdup (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  apr_pstrmemdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_fs_x__change_t *
path_change_dup(const svn_fs_x__change_t *source,
                apr_pool_t *result_pool)
{
  svn_fs_x__change_t *result
    = apr_pmemdup(result_pool, source, sizeof(*source));
  result->path.data
    = apr_pstrmemdup(result_pool, source->path.data, source->path.len);

  if (source->copyfrom_path)
    result->copyfrom_path = apr_pstrdup(result_pool, source->copyfrom_path);

  return result;
}