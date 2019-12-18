#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
struct TYPE_23__ {int /*<<< orphan*/  second; int /*<<< orphan*/  revision; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ svn_fs_x__pair_cache_key_t ;
struct TYPE_24__ {int /*<<< orphan*/  revprop_cache; int /*<<< orphan*/  revprop_generation; } ;
typedef  TYPE_2__ svn_fs_x__data_t ;
struct TYPE_25__ {TYPE_2__* fsap_data; } ;
typedef  TYPE_3__ svn_fs_t ;
struct TYPE_26__ {int /*<<< orphan*/  apr_err; } ;
typedef  TYPE_4__ svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
struct TYPE_27__ {int /*<<< orphan*/ * properties; } ;
typedef  TYPE_5__ packed_revprops_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_STATUS_IS_ENOENT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_NO_SUCH_REVISION ; 
 TYPE_4__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ has_revprop_cache (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_generation_valid (TYPE_3__*) ; 
 TYPE_4__* read_non_packed_revprop (int /*<<< orphan*/ **,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_pack_revprop (TYPE_5__**,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_revprop_generation (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_cache__get (void**,scalar_t__*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_4__*) ; 
 TYPE_4__* svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* svn_error_trace (TYPE_4__*) ; 
 int /*<<< orphan*/  svn_fs_x__ensure_revision_exists (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__is_packed_revprop (TYPE_3__*,int /*<<< orphan*/ ) ; 

svn_error_t *
svn_fs_x__get_revision_proplist(apr_hash_t **proplist_p,
                                svn_fs_t *fs,
                                svn_revnum_t rev,
                                svn_boolean_t bypass_cache,
                                svn_boolean_t refresh,
                                apr_pool_t *result_pool,
                                apr_pool_t *scratch_pool)
{
  svn_fs_x__data_t *ffd = fs->fsap_data;

  /* not found, yet */
  *proplist_p = NULL;

  /* should they be available at all? */
  SVN_ERR(svn_fs_x__ensure_revision_exists(rev, fs, scratch_pool));

  /* Ensure that the revprop generation info is valid. */
  if (refresh || !is_generation_valid(fs))
    SVN_ERR(read_revprop_generation(fs, scratch_pool));

  /* Try cache lookup first. */
  if (!bypass_cache && has_revprop_cache(fs, scratch_pool))
    {
      svn_boolean_t is_cached;
      svn_fs_x__pair_cache_key_t key = { 0 };

      key.revision = rev;
      key.second = ffd->revprop_generation;
      SVN_ERR(svn_cache__get((void **) proplist_p, &is_cached,
                             ffd->revprop_cache, &key, result_pool));
      if (is_cached)
        return SVN_NO_ERROR;
    }

  /* if REV had not been packed when we began, try reading it from the
   * non-packed shard.  If that fails, we will fall through to packed
   * shard reads. */
  if (!svn_fs_x__is_packed_revprop(fs, rev))
    {
      svn_error_t *err = read_non_packed_revprop(proplist_p, fs, rev,
                                                 result_pool, scratch_pool);
      if (err)
        {
          if (!APR_STATUS_IS_ENOENT(err->apr_err))
            return svn_error_trace(err);

          svn_error_clear(err);
          *proplist_p = NULL; /* in case read_non_packed_revprop changed it */
        }
    }

  /* if revprop packing is available and we have not read the revprops, yet,
   * try reading them from a packed shard.  If that fails, REV is most
   * likely invalid (or its revprops highly contested). */
  if (!*proplist_p)
    {
      packed_revprops_t *revprops;
      SVN_ERR(read_pack_revprop(&revprops, fs, rev, FALSE,
                                result_pool, scratch_pool));
      *proplist_p = revprops->properties;
    }

  /* The revprops should have been there. Did we get them? */
  if (!*proplist_p)
    return svn_error_createf(SVN_ERR_FS_NO_SUCH_REVISION, NULL,
                             _("Could not read revprops for revision %ld"),
                             rev);

  return SVN_NO_ERROR;
}