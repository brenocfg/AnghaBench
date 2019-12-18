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
struct TYPE_7__ {int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_8__ {char const* post_commit_err; int /*<<< orphan*/ * author; int /*<<< orphan*/ * date; int /*<<< orphan*/  revision; } ;
typedef  TYPE_2__ svn_commit_info_t ;
typedef  int /*<<< orphan*/  (* svn_commit_callback2_t ) (TYPE_2__*,void*,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_REVISION_AUTHOR ; 
 int /*<<< orphan*/  SVN_PROP_REVISION_DATE ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_2__* svn_create_commit_info (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_revision_proplist2 (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_hash_gets (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
invoke_commit_cb(svn_commit_callback2_t commit_cb,
                 void *commit_baton,
                 svn_fs_t *fs,
                 svn_revnum_t revision,
                 const char *post_commit_errstr,
                 apr_pool_t *scratch_pool)
{
  /* FS interface returns non-const values.  */
  /* const */ svn_string_t *date;
  /* const */ svn_string_t *author;
  svn_commit_info_t *commit_info;
  apr_hash_t *revprops;

  if (commit_cb == NULL)
    return SVN_NO_ERROR;

  SVN_ERR(svn_fs_revision_proplist2(&revprops, fs, revision,
                                    TRUE, scratch_pool, scratch_pool));

  date = svn_hash_gets(revprops, SVN_PROP_REVISION_DATE);
  author = svn_hash_gets(revprops, SVN_PROP_REVISION_AUTHOR);

  commit_info = svn_create_commit_info(scratch_pool);

  /* fill up the svn_commit_info structure */
  commit_info->revision = revision;
  commit_info->date = date ? date->data : NULL;
  commit_info->author = author ? author->data : NULL;
  commit_info->post_commit_err = post_commit_errstr;
  /* commit_info->repos_root is not set by the repos layer, only by RA layers */

  return svn_error_trace(commit_cb(commit_info, commit_baton, scratch_pool));
}