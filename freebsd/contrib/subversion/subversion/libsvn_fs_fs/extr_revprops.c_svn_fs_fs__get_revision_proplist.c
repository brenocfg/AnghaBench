#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
struct TYPE_22__ {TYPE_5__* fsap_data; } ;
typedef  TYPE_1__ svn_fs_t ;
struct TYPE_23__ {int /*<<< orphan*/  apr_err; } ;
typedef  TYPE_2__ svn_error_t ;
typedef  int svn_boolean_t ;
struct TYPE_24__ {int /*<<< orphan*/  second; int /*<<< orphan*/  revision; } ;
typedef  TYPE_3__ pair_cache_key_t ;
struct TYPE_25__ {int /*<<< orphan*/ * properties; } ;
typedef  TYPE_4__ packed_revprops_t ;
struct TYPE_26__ {scalar_t__ format; int /*<<< orphan*/  revprop_cache; int /*<<< orphan*/  revprop_prefix; } ;
typedef  TYPE_5__ fs_fs_data_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_STATUS_IS_ENOENT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_NO_SUCH_REVISION ; 
 int /*<<< orphan*/  SVN_ERR_W (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_FS_FS__MIN_PACKED_REVPROP_FORMAT ; 
 TYPE_2__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  apr_psprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prepare_revprop_cache (TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_2__* read_non_packed_revprop (int /*<<< orphan*/ **,TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_pack_revprop (TYPE_4__**,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_cache__get (void**,int*,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_2__*) ; 
 TYPE_2__* svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* svn_error_trace (TYPE_2__*) ; 
 int /*<<< orphan*/  svn_fs_fs__ensure_revision_exists (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__is_packed_revprop (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_fs__reset_revprop_cache (TYPE_1__*) ; 

svn_error_t *
svn_fs_fs__get_revision_proplist(apr_hash_t **proplist_p,
                                 svn_fs_t *fs,
                                 svn_revnum_t rev,
                                 svn_boolean_t refresh,
                                 apr_pool_t *result_pool,
                                 apr_pool_t *scratch_pool)
{
  fs_fs_data_t *ffd = fs->fsap_data;

  /* Only populate the cache if we did not just cross a sync barrier.
   * This is to eliminate overhead from code that always sets REFRESH.
   * For callers that want caching, the caching kicks in on read "later". */
  svn_boolean_t populate_cache = !refresh;

  /* not found, yet */
  *proplist_p = NULL;

  /* should they be available at all? */
  SVN_ERR(svn_fs_fs__ensure_revision_exists(rev, fs, scratch_pool));

  if (refresh)
    {
      /* Previous cache contents is invalid now. */
      svn_fs_fs__reset_revprop_cache(fs);
    }
  else
    {
      /* Try cache lookup first. */
      svn_boolean_t is_cached;
      pair_cache_key_t key;

      /* Auto-alloc prefix and construct the key. */
      SVN_ERR(prepare_revprop_cache(fs, scratch_pool));
      key.revision = rev;
      key.second = ffd->revprop_prefix;

      /* The only way that this might error out is due to parser error. */
      SVN_ERR_W(svn_cache__get((void **) proplist_p, &is_cached,
                               ffd->revprop_cache, &key, result_pool),
                apr_psprintf(scratch_pool,
                             "Failed to parse revprops for r%ld.",
                             rev));
      if (is_cached)
        return SVN_NO_ERROR;
    }

  /* if REV had not been packed when we began, try reading it from the
   * non-packed shard.  If that fails, we will fall through to packed
   * shard reads. */
  if (!svn_fs_fs__is_packed_revprop(fs, rev))
    {
      svn_error_t *err = read_non_packed_revprop(proplist_p, fs, rev,
                                                 populate_cache, result_pool);
      if (err)
        {
          if (!APR_STATUS_IS_ENOENT(err->apr_err)
              || ffd->format < SVN_FS_FS__MIN_PACKED_REVPROP_FORMAT)
            return svn_error_trace(err);

          svn_error_clear(err);
          *proplist_p = NULL; /* in case read_non_packed_revprop changed it */
        }
    }

  /* if revprop packing is available and we have not read the revprops, yet,
   * try reading them from a packed shard.  If that fails, REV is most
   * likely invalid (or its revprops highly contested). */
  if (ffd->format >= SVN_FS_FS__MIN_PACKED_REVPROP_FORMAT && !*proplist_p)
    {
      packed_revprops_t *revprops;
      SVN_ERR(read_pack_revprop(&revprops, fs, rev, FALSE, populate_cache,
                                result_pool));
      *proplist_p = revprops->properties;
    }

  /* The revprops should have been there. Did we get them? */
  if (!*proplist_p)
    return svn_error_createf(SVN_ERR_FS_NO_SUCH_REVISION, NULL,
                             _("Could not read revprops for revision %ld"),
                             rev);

  return SVN_NO_ERROR;
}