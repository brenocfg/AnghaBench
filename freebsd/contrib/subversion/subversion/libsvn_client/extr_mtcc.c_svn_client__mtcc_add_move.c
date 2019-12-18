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
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_6__ {int /*<<< orphan*/  base_revision; } ;
typedef  TYPE_1__ svn_client__mtcc_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  mtcc_add_delete (char const*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtcc_get_origin (char const**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client__mtcc_add_copy (char const*,int /*<<< orphan*/ ,char const*,TYPE_1__*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_client__mtcc_add_move(const char *src_relpath,
                          const char *dst_relpath,
                          svn_client__mtcc_t *mtcc,
                          apr_pool_t *scratch_pool)
{
  const char *origin_relpath;
  svn_revnum_t origin_rev;

  SVN_ERR(mtcc_get_origin(&origin_relpath, &origin_rev,
                          src_relpath, FALSE, mtcc,
                          scratch_pool, scratch_pool));

  SVN_ERR(svn_client__mtcc_add_copy(src_relpath, mtcc->base_revision,
                                    dst_relpath, mtcc, scratch_pool));
  SVN_ERR(mtcc_add_delete(src_relpath, TRUE, mtcc, scratch_pool));

  return SVN_NO_ERROR;
}