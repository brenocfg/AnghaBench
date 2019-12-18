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
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_4__ {int /*<<< orphan*/  revision; } ;
typedef  TYPE_1__ svn_commit_info_t ;
struct deltify_etc_baton {int /*<<< orphan*/  fs; int /*<<< orphan*/  repos; int /*<<< orphan*/  fspath_base; scalar_t__ lock_tokens; int /*<<< orphan*/  commit_baton; int /*<<< orphan*/ * (* commit_cb ) (TYPE_1__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 void* apr_hash_this_key (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_val (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub1 (TYPE_1__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_compose_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_fs_deltify_revision (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* svn_fspath__join (int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_repos_fs_unlock_many (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
deltify_etc(const svn_commit_info_t *commit_info,
            void *baton,
            apr_pool_t *scratch_pool)
{
  struct deltify_etc_baton *deb = baton;
  svn_error_t *err1 = SVN_NO_ERROR;
  svn_error_t *err2;

  /* Invoke the original callback first, in case someone's waiting to
     know the revision number so they can go off and annotate an
     issue or something. */
  if (deb->commit_cb)
    err1 = deb->commit_cb(commit_info, deb->commit_baton, scratch_pool);

  /* Maybe unlock the paths. */
  if (deb->lock_tokens)
    {
      apr_pool_t *subpool = svn_pool_create(scratch_pool);
      apr_hash_t *targets = apr_hash_make(subpool);
      apr_hash_index_t *hi;

      for (hi = apr_hash_first(subpool, deb->lock_tokens); hi;
           hi = apr_hash_next(hi))
        {
          const void *relpath = apr_hash_this_key(hi);
          const char *token = apr_hash_this_val(hi);
          const char *fspath;

          fspath = svn_fspath__join(deb->fspath_base, relpath, subpool);
          svn_hash_sets(targets, fspath, token);
        }

      /* We may get errors here if the lock was broken or stolen
         after the commit succeeded.  This is fine and should be
         ignored. */
      svn_error_clear(svn_repos_fs_unlock_many(deb->repos, targets, FALSE,
                                               NULL, NULL,
                                               subpool, subpool));

      svn_pool_destroy(subpool);
    }

  /* But, deltification shouldn't be stopped just because someone's
     random callback failed, so proceed unconditionally on to
     deltification. */
  err2 = svn_fs_deltify_revision(deb->fs, commit_info->revision, scratch_pool);

  return svn_error_compose_create(err1, err2);
}