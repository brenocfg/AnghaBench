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
typedef  int /*<<< orphan*/  svn_fs_x__noderev_t ;
typedef  int /*<<< orphan*/  svn_fs_x__id_t ;
struct TYPE_7__ {scalar_t__ txn_filesize; TYPE_2__* entries; } ;
typedef  TYPE_1__ svn_fs_x__dir_data_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  scalar_t__ svn_filesize_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_cache__t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_8__ {int nelts; } ;
typedef  TYPE_2__ apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  get_dir_contents (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_txn_dir_info (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * locate_dir_cache (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_cache__get (void**,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_cache__is_cachable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svn_cache__set (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_x__rep_contents_dir(apr_array_header_t **entries_p,
                           svn_fs_t *fs,
                           svn_fs_x__noderev_t *noderev,
                           apr_pool_t *result_pool,
                           apr_pool_t *scratch_pool)
{
  svn_fs_x__id_t key;
  svn_fs_x__dir_data_t *dir;

  /* find the cache we may use */
  svn_cache__t *cache = locate_dir_cache(fs, &key, noderev);
  svn_boolean_t found;

  SVN_ERR(svn_cache__get((void **)&dir, &found, cache, &key, result_pool));
  if (found)
    {
      /* Verify that the cached dir info is not stale
       * (no-op for committed data). */
      svn_filesize_t filesize;
      SVN_ERR(get_txn_dir_info(&filesize, fs, noderev, scratch_pool));

      if (filesize == dir->txn_filesize)
        {
          /* Still valid. Done. */
          *entries_p = dir->entries;
          return SVN_NO_ERROR;
        }
    }

  /* Read in the directory contents. */
  dir = apr_pcalloc(scratch_pool, sizeof(*dir));
  SVN_ERR(get_dir_contents(dir, fs, noderev, result_pool, scratch_pool));
  *entries_p = dir->entries;

  /* Update the cache, if we are to use one.
   *
   * Don't even attempt to serialize very large directories; it would cause
   * an unnecessary memory allocation peak.  100 bytes/entry is about right.
   */
  if (svn_cache__is_cachable(cache, 100 * dir->entries->nelts))
    SVN_ERR(svn_cache__set(cache, &key, dir, scratch_pool));

  return SVN_NO_ERROR;
}