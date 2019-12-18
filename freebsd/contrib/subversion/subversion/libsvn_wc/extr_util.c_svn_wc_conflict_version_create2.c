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
struct TYPE_4__ {char const* repos_url; char const* path_in_repos; char const* repos_uuid; int /*<<< orphan*/  node_kind; int /*<<< orphan*/  peg_rev; } ;
typedef  TYPE_1__ svn_wc_conflict_version_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_node_kind_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_ASSERT_NO_RETURN (int) ; 
 scalar_t__ SVN_IS_VALID_REVNUM (int /*<<< orphan*/ ) ; 
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 scalar_t__ svn_relpath_is_canonical (char const*) ; 
 scalar_t__ svn_uri_is_canonical (char const*,int /*<<< orphan*/ *) ; 

svn_wc_conflict_version_t *
svn_wc_conflict_version_create2(const char *repos_url,
                                const char *repos_uuid,
                                const char *repos_relpath,
                                svn_revnum_t revision,
                                svn_node_kind_t kind,
                                apr_pool_t *result_pool)
{
  svn_wc_conflict_version_t *version;

  version = apr_pcalloc(result_pool, sizeof(*version));

    SVN_ERR_ASSERT_NO_RETURN(svn_uri_is_canonical(repos_url, result_pool)
                             && svn_relpath_is_canonical(repos_relpath)
                             && SVN_IS_VALID_REVNUM(revision)
                             /* ### repos_uuid can be NULL :( */);

  version->repos_url = repos_url;
  version->peg_rev = revision;
  version->path_in_repos = repos_relpath;
  version->node_kind = kind;
  version->repos_uuid = repos_uuid;

  return version;
}