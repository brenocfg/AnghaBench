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
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_checksum_t ;
struct edit_baton {int /*<<< orphan*/  cancel_baton; int /*<<< orphan*/  cancel_func; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 char* FSPATH (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  alter_props (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  can_modify (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_root (int /*<<< orphan*/ **,struct edit_baton*) ; 
 int /*<<< orphan*/  set_text (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
alter_file_cb(void *baton,
              const char *relpath,
              svn_revnum_t revision,
              const svn_checksum_t *checksum,
              svn_stream_t *contents,
              apr_hash_t *props,
              apr_pool_t *scratch_pool)
{
  struct edit_baton *eb = baton;
  const char *fspath = FSPATH(relpath, scratch_pool);
  svn_fs_root_t *root;

  SVN_ERR(get_root(&root, eb));
  SVN_ERR(can_modify(root, fspath, revision, scratch_pool));

  if (contents != NULL)
    {
      SVN_ERR_ASSERT(checksum != NULL);
      SVN_ERR(set_text(root, fspath, checksum, contents,
                       eb->cancel_func, eb->cancel_baton, scratch_pool));
    }

  if (props != NULL)
    {
      SVN_ERR(alter_props(root, fspath, props, scratch_pool));
    }

  return SVN_NO_ERROR;
}