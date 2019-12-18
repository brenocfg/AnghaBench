#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ kind; int /*<<< orphan*/  mtime; } ;
typedef  TYPE_1__ svn_io_dirent2_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_9__ {int /*<<< orphan*/  patch_path; int /*<<< orphan*/  message; TYPE_1__* dirent; int /*<<< orphan*/  mtime; } ;
typedef  TYPE_2__ svn_client_shelved_patch_info_t ;
struct TYPE_10__ {int /*<<< orphan*/  wc_ctx; } ;
typedef  TYPE_3__ svn_client_ctx_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_key (int /*<<< orphan*/ *) ; 
 TYPE_1__* apr_hash_this_val (int /*<<< orphan*/ *) ; 
 TYPE_2__* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  read_logmsg_from_patch (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shelf_name_from_filename (char**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_join (char*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,char*,TYPE_2__*) ; 
 int /*<<< orphan*/  svn_io_get_dirents3 (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_file ; 
 int /*<<< orphan*/  svn_wc__get_shelves_dir (char**,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_client_shelves_list(apr_hash_t **shelved_patch_infos,
                        const char *local_abspath,
                        svn_client_ctx_t *ctx,
                        apr_pool_t *result_pool,
                        apr_pool_t *scratch_pool)
{
  char *shelves_dir;
  apr_hash_t *dirents;
  apr_hash_index_t *hi;

  SVN_ERR(svn_wc__get_shelves_dir(&shelves_dir, ctx->wc_ctx, local_abspath,
                                  scratch_pool, scratch_pool));
  SVN_ERR(svn_io_get_dirents3(&dirents, shelves_dir, FALSE /*only_check_type*/,
                              result_pool, scratch_pool));

  *shelved_patch_infos = apr_hash_make(result_pool);

  /* Remove non-shelves */
  for (hi = apr_hash_first(scratch_pool, dirents); hi; hi = apr_hash_next(hi))
    {
      const char *filename = apr_hash_this_key(hi);
      svn_io_dirent2_t *dirent = apr_hash_this_val(hi);
      char *name = NULL;

      svn_error_clear(shelf_name_from_filename(&name, filename, result_pool));
      if (name && dirent->kind == svn_node_file)
        {
          svn_client_shelved_patch_info_t *info
            = apr_palloc(result_pool, sizeof(*info));

          info->dirent = dirent;
          info->mtime = info->dirent->mtime;
          info->patch_path
            = svn_dirent_join(shelves_dir, filename, result_pool);
          SVN_ERR(read_logmsg_from_patch(&info->message, info->patch_path,
                                         result_pool, scratch_pool));

          svn_hash_sets(*shelved_patch_infos, name, info);
        }
    }

  return SVN_NO_ERROR;
}