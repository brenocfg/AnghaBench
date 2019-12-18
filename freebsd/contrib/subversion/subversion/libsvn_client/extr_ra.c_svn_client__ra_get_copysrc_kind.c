#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct ra_ev2_baton {int /*<<< orphan*/  wc_ctx; int /*<<< orphan*/  relpath_map; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 char* svn_hash_gets (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_node_unknown ; 
 int /*<<< orphan*/  svn_wc_read_kind2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_client__ra_get_copysrc_kind(svn_node_kind_t *kind,
                                void *baton,
                                const char *repos_relpath,
                                svn_revnum_t src_revision,
                                apr_pool_t *scratch_pool)
{
  struct ra_ev2_baton *reb = baton;
  const char *local_abspath;

  local_abspath = svn_hash_gets(reb->relpath_map, repos_relpath);
  if (!local_abspath)
    {
      *kind = svn_node_unknown;
      return SVN_NO_ERROR;
    }

  /* ### what to do with SRC_REVISION?  */

  SVN_ERR(svn_wc_read_kind2(kind, reb->wc_ctx, local_abspath,
                            FALSE, FALSE, scratch_pool));

  return SVN_NO_ERROR;
}