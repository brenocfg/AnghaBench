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
struct shim_callbacks_baton {int /*<<< orphan*/  wc_ctx; int /*<<< orphan*/  relpath_map; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 char* svn_hash_gets (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_node_unknown ; 
 int /*<<< orphan*/  svn_wc_read_kind2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
fetch_kind_func(svn_node_kind_t *kind,
                void *baton,
                const char *path,
                svn_revnum_t base_revision,
                apr_pool_t *scratch_pool)
{
  struct shim_callbacks_baton *scb = baton;
  const char *local_abspath;

  local_abspath = svn_hash_gets(scb->relpath_map, path);
  if (!local_abspath)
    {
      *kind = svn_node_unknown;
      return SVN_NO_ERROR;
    }
  /* Reads the WORKING kind. Not the BASE kind */
  SVN_ERR(svn_wc_read_kind2(kind, scb->wc_ctx, local_abspath,
                            TRUE, FALSE, scratch_pool));

  return SVN_NO_ERROR;
}