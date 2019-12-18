#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_wc__db_wcroot_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  scalar_t__ svn_wc__db_status_t ;
typedef  int /*<<< orphan*/  svn_skel_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_4__ {char const* repos_root_url; char const* repos_uuid; char const* repos_relpath; int /*<<< orphan*/  const* work_items; int /*<<< orphan*/  const* conflict; int /*<<< orphan*/ * target; int /*<<< orphan*/ * checksum; int /*<<< orphan*/  depth; int /*<<< orphan*/ * children; int /*<<< orphan*/  revision; int /*<<< orphan*/  kind; scalar_t__ status; } ;
typedef  TYPE_1__ insert_base_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int SVN_IS_VALID_REVNUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_WC__DB_WITH_TXN (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VERIFY_USABLE_WCROOT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blank_ibb (TYPE_1__*) ; 
 int /*<<< orphan*/  flush_entries (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  insert_base_node (TYPE_1__*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_depth_infinity ; 
 int /*<<< orphan*/  svn_depth_unknown ; 
 int svn_dirent_is_absolute (char const*) ; 
 int /*<<< orphan*/  svn_dirent_split (char const**,char const**,char const*,int /*<<< orphan*/ *) ; 
 char* svn_relpath_join (char const*,char const*,int /*<<< orphan*/ *) ; 
 int svn_uri_is_canonical (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc__db_status_excluded ; 
 scalar_t__ svn_wc__db_status_not_present ; 
 scalar_t__ svn_wc__db_status_server_excluded ; 
 int /*<<< orphan*/  svn_wc__db_wcroot_parse_local_abspath (int /*<<< orphan*/ **,char const**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
add_excluded_or_not_present_node(svn_wc__db_t *db,
                                 const char *local_abspath,
                                 const char *repos_relpath,
                                 const char *repos_root_url,
                                 const char *repos_uuid,
                                 svn_revnum_t revision,
                                 svn_node_kind_t kind,
                                 svn_wc__db_status_t status,
                                 const svn_skel_t *conflict,
                                 const svn_skel_t *work_items,
                                 apr_pool_t *scratch_pool)
{
  svn_wc__db_wcroot_t *wcroot;
  const char *local_relpath;
  insert_base_baton_t ibb;
  const char *dir_abspath, *name;

  SVN_ERR_ASSERT(svn_dirent_is_absolute(local_abspath));
  SVN_ERR_ASSERT(repos_relpath != NULL);
  SVN_ERR_ASSERT(svn_uri_is_canonical(repos_root_url, scratch_pool));
  SVN_ERR_ASSERT(repos_uuid != NULL);
  SVN_ERR_ASSERT(SVN_IS_VALID_REVNUM(revision));
  SVN_ERR_ASSERT(status == svn_wc__db_status_server_excluded
                 || status == svn_wc__db_status_excluded
                 || status == svn_wc__db_status_not_present);

  /* These absent presence nodes are only useful below a parent node that is
     present. To avoid problems with working copies obstructing the child
     we calculate the wcroot and local_relpath of the parent and then add
     our own relpath. */

  svn_dirent_split(&dir_abspath, &name, local_abspath, scratch_pool);

  SVN_ERR(svn_wc__db_wcroot_parse_local_abspath(&wcroot, &local_relpath, db,
                              dir_abspath, scratch_pool, scratch_pool));
  VERIFY_USABLE_WCROOT(wcroot);

  local_relpath = svn_relpath_join(local_relpath, name, scratch_pool);

  blank_ibb(&ibb);

  /* Calculate repos_id in insert_base_node() to avoid extra transaction */
  ibb.repos_root_url = repos_root_url;
  ibb.repos_uuid = repos_uuid;

  ibb.status = status;
  ibb.kind = kind;
  ibb.repos_relpath = repos_relpath;
  ibb.revision = revision;

  /* Depending upon KIND, any of these might get used. */
  ibb.children = NULL;
  ibb.depth = svn_depth_unknown;
  ibb.checksum = NULL;
  ibb.target = NULL;

  ibb.conflict = conflict;
  ibb.work_items = work_items;

  SVN_WC__DB_WITH_TXN(
            insert_base_node(&ibb, wcroot, local_relpath, scratch_pool),
            wcroot);

  /* If this used to be a directory we should remove children so pass
   * depth infinity. */
  SVN_ERR(flush_entries(wcroot, local_abspath, svn_depth_infinity,
                        scratch_pool));

  return SVN_NO_ERROR;
}