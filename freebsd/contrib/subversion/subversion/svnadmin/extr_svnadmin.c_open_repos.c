#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_repos_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int svn_boolean_t ;
struct svnadmin_opt_state {scalar_t__ no_flush_to_disk; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
struct TYPE_2__ {scalar_t__ cache_size; } ;

/* Variables and functions */
 scalar_t__ BLOCK_READ_CACHE_THRESHOLD ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_FS_CONFIG_FSFS_BLOCK_READ ; 
 int /*<<< orphan*/  SVN_FS_CONFIG_FSFS_CACHE_DELTAS ; 
 int /*<<< orphan*/  SVN_FS_CONFIG_FSFS_CACHE_FULLTEXTS ; 
 int /*<<< orphan*/  SVN_FS_CONFIG_FSFS_CACHE_NODEPROPS ; 
 int /*<<< orphan*/  SVN_FS_CONFIG_FSFS_CACHE_NS ; 
 int /*<<< orphan*/  SVN_FS_CONFIG_FSFS_CACHE_REVPROPS ; 
 int /*<<< orphan*/  SVN_FS_CONFIG_NO_FLUSH_TO_DISK ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_cache_config_get () ; 
 int /*<<< orphan*/  svn_fs_set_warning_func (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  svn_repos_fs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_repos_open3 (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* svn_uuid_generate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  warning_func ; 

__attribute__((used)) static svn_error_t *
open_repos(svn_repos_t **repos,
           const char *path,
           struct svnadmin_opt_state *opt_state,
           apr_pool_t *pool)
{
  /* Enable the "block-read" feature (where it applies)? */
  svn_boolean_t use_block_read
    = svn_cache_config_get()->cache_size > BLOCK_READ_CACHE_THRESHOLD;

  /* construct FS configuration parameters: enable caches for r/o data */
  apr_hash_t *fs_config = apr_hash_make(pool);
  svn_hash_sets(fs_config, SVN_FS_CONFIG_FSFS_CACHE_DELTAS, "1");
  svn_hash_sets(fs_config, SVN_FS_CONFIG_FSFS_CACHE_FULLTEXTS, "1");
  svn_hash_sets(fs_config, SVN_FS_CONFIG_FSFS_CACHE_NODEPROPS, "1");
  svn_hash_sets(fs_config, SVN_FS_CONFIG_FSFS_CACHE_REVPROPS, "2");
  svn_hash_sets(fs_config, SVN_FS_CONFIG_FSFS_CACHE_NS,
                           svn_uuid_generate(pool));
  svn_hash_sets(fs_config, SVN_FS_CONFIG_FSFS_BLOCK_READ,
                           use_block_read ? "1" : "0");
  svn_hash_sets(fs_config, SVN_FS_CONFIG_NO_FLUSH_TO_DISK,
                           opt_state->no_flush_to_disk ? "1" : "0");

  /* now, open the requested repository */
  SVN_ERR(svn_repos_open3(repos, path, fs_config, pool, pool));
  svn_fs_set_warning_func(svn_repos_fs(*repos), warning_func, NULL);
  return SVN_NO_ERROR;
}