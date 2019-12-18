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
struct TYPE_3__ {char* path_in_repos; char* repos_url; int /*<<< orphan*/  peg_rev; int /*<<< orphan*/  node_kind; } ;
typedef  TYPE_1__ svn_wc_conflict_version_t ;
typedef  int /*<<< orphan*/  svn_skel_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 char* apr_psprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_valid_version_info_skel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  node_kind_map ; 
 int /*<<< orphan*/  skel_prepend_enum (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_skel__make_empty_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_skel__prepend (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_skel__str_atom (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
prepend_version_info_skel(svn_skel_t *parent_skel,
                          const svn_wc_conflict_version_t *version_info,
                          apr_pool_t *pool)
{
  svn_skel_t *skel = svn_skel__make_empty_list(pool);

  /* node_kind */
  skel_prepend_enum(skel, node_kind_map, version_info->node_kind, pool);

  /* path_in_repos */
  svn_skel__prepend(svn_skel__str_atom(version_info->path_in_repos
                                       ? version_info->path_in_repos
                                       : "", pool), skel);

  /* peg_rev */
  svn_skel__prepend(svn_skel__str_atom(apr_psprintf(pool, "%ld",
                                                    version_info->peg_rev),
                                       pool), skel);

  /* repos_url */
  svn_skel__prepend(svn_skel__str_atom(version_info->repos_url
                                       ? version_info->repos_url
                                       : "", pool), skel);

  svn_skel__prepend(svn_skel__str_atom("version", pool), skel);

  SVN_ERR_ASSERT(is_valid_version_info_skel(skel));

  svn_skel__prepend(skel, parent_skel);

  return SVN_NO_ERROR;
}