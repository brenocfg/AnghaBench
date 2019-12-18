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
struct TYPE_3__ {int /*<<< orphan*/  config; } ;
typedef  TYPE_1__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_FS_CONFIG_FSFS_CACHE_DELTAS ; 
 int /*<<< orphan*/  SVN_FS_CONFIG_FSFS_CACHE_FULLTEXTS ; 
 int /*<<< orphan*/  SVN_FS_CONFIG_FSFS_CACHE_NODEPROPS ; 
 int /*<<< orphan*/  SVN_FS_CONFIG_FSFS_CACHE_NS ; 
 int /*<<< orphan*/  SVN_FS_CONFIG_FSFS_CACHE_REVPROPS ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 char* normalize_key_part (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  svn_hash__get_bool (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_hash__get_cstring (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static svn_error_t *
read_config(const char **cache_namespace,
            svn_boolean_t *cache_txdeltas,
            svn_boolean_t *cache_fulltexts,
            svn_boolean_t *cache_revprops,
            svn_boolean_t *cache_nodeprops,
            svn_fs_t *fs,
            apr_pool_t *result_pool)
{
  /* No cache namespace by default.  I.e. all FS instances share the
   * cached data.  If you specify different namespaces, the data will
   * share / compete for the same cache memory but keys will not match
   * across namespaces and, thus, cached data will not be shared between
   * namespaces.
   *
   * Since the namespace will be concatenated with other elements to form
   * the complete key prefix, we must make sure that the resulting string
   * is unique and cannot be created by any other combination of elements.
   */
  *cache_namespace
    = normalize_key_part(svn_hash__get_cstring(fs->config,
                                               SVN_FS_CONFIG_FSFS_CACHE_NS,
                                               ""),
                         result_pool);

  /* don't cache text deltas by default.
   * Once we reconstructed the fulltexts from the deltas,
   * these deltas are rarely re-used. Therefore, only tools
   * like svnadmin will activate this to speed up operations
   * dump and verify.
   */
  *cache_txdeltas
    = svn_hash__get_bool(fs->config,
                         SVN_FS_CONFIG_FSFS_CACHE_DELTAS,
                         TRUE);

  /* by default, cache fulltexts.
   * Most SVN tools care about reconstructed file content.
   * Thus, this is a reasonable default.
   * SVN admin tools may set that to FALSE because fulltexts
   * won't be re-used rendering the cache less effective
   * by squeezing wanted data out.
   */
  *cache_fulltexts
    = svn_hash__get_bool(fs->config,
                         SVN_FS_CONFIG_FSFS_CACHE_FULLTEXTS,
                         TRUE);

  /* don't cache revprops by default.
   * Revprop caching significantly speeds up operations like
   * svn ls -v. However, it requires synchronization that may
   * not be available or efficient in the current server setup.
   * Option "2" is equivalent to "1".
   */
  if (strcmp(svn_hash__get_cstring(fs->config,
                                   SVN_FS_CONFIG_FSFS_CACHE_REVPROPS,
                                   ""), "2"))
    *cache_revprops
      = svn_hash__get_bool(fs->config,
                          SVN_FS_CONFIG_FSFS_CACHE_REVPROPS,
                          FALSE);
  else
    *cache_revprops = TRUE;

  /* by default, cache nodeprops: this will match pre-1.10
   * behavior where node properties caching was controlled
   * by SVN_FS_CONFIG_FSFS_CACHE_FULLTEXTS configuration option.
   */
  *cache_nodeprops
    = svn_hash__get_bool(fs->config,
                         SVN_FS_CONFIG_FSFS_CACHE_NODEPROPS,
                         TRUE);

  return SVN_NO_ERROR;
}