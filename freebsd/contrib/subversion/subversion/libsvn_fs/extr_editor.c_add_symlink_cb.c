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
typedef  int /*<<< orphan*/  svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct edit_baton {int dummy; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_HASH_KEY_STRING ; 
 char* FSPATH (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_IS_VALID_REVNUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_PROP_SPECIAL ; 
 int /*<<< orphan*/  SVN_PROP_SPECIAL_VALUE ; 
 int /*<<< orphan*/  SVN__NOT_IMPLEMENTED () ; 
 int /*<<< orphan*/  add_new_props (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  can_create (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  can_modify (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fs_contents ; 
 int /*<<< orphan*/  get_root (int /*<<< orphan*/ **,struct edit_baton*) ; 
 int /*<<< orphan*/  svn_fs_apply_text (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_delete (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_make_file (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
add_symlink_cb(void *baton,
               const char *relpath,
               const char *target,
               apr_hash_t *props,
               svn_revnum_t replaces_rev,
               apr_pool_t *scratch_pool)
{
  struct edit_baton *eb = baton;
  const char *fspath = FSPATH(relpath, scratch_pool);
  svn_fs_root_t *root;

  SVN_ERR(get_root(&root, eb));

  if (SVN_IS_VALID_REVNUM(replaces_rev))
    {
      SVN_ERR(can_modify(root, fspath, replaces_rev, scratch_pool));
      SVN_ERR(svn_fs_delete(root, fspath, scratch_pool));
    }
  else
    {
      SVN_ERR(can_create(root, fspath, scratch_pool));
    }

  /* ### we probably need to construct a file with specific contents
     ### (until the FS grows some symlink APIs)  */
#if 0
  SVN_ERR(svn_fs_make_file(root, fspath, scratch_pool));
  SVN_ERR(svn_fs_apply_text(&fs_contents, root, fspath,
                            NULL /* result_checksum */,
                            scratch_pool));
  /* ### SVN_ERR(svn_stream_printf(fs_contents, ..., scratch_pool));  */
  apr_hash_set(props, SVN_PROP_SPECIAL, APR_HASH_KEY_STRING,
               SVN_PROP_SPECIAL_VALUE);

  SVN_ERR(add_new_props(root, fspath, props, scratch_pool));
#endif

  SVN__NOT_IMPLEMENTED();
}