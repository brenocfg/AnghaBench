#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_9__ {TYPE_1__* editor; int /*<<< orphan*/  add_props_included; } ;
typedef  TYPE_2__ report_context_t ;
struct TYPE_10__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  final_md5_checksum; int /*<<< orphan*/  file_baton; scalar_t__ url; int /*<<< orphan*/  base_rev; int /*<<< orphan*/  found_lock_prop; scalar_t__ lock_token; scalar_t__ remove_props; TYPE_4__* parent_dir; } ;
typedef  TYPE_3__ file_baton_t ;
struct TYPE_11__ {TYPE_2__* ctx; } ;
typedef  TYPE_4__ dir_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;
struct TYPE_8__ {int /*<<< orphan*/  (* close_file ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* change_file_prop ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_IS_VALID_REVNUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_ENTRY_LOCK_TOKEN ; 
 int /*<<< orphan*/  SVN_RA_SERF__WC_CHECKED_IN_URL ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_this_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ensure_file_opened (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  maybe_close_dir (TYPE_4__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_checksum_to_cstring (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_string_create (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
close_file(file_baton_t *file,
           apr_pool_t *scratch_pool)
{
  dir_baton_t *parent_dir = file->parent_dir;
  report_context_t *ctx = parent_dir->ctx;

  SVN_ERR(ensure_file_opened(file, scratch_pool));

  /* Set all of the properties we received */
  if (file->remove_props)
    {
      apr_hash_index_t *hi;

      for (hi = apr_hash_first(scratch_pool, file->remove_props);
           hi;
           hi = apr_hash_next(hi))
        {
          SVN_ERR(ctx->editor->change_file_prop(file->file_baton,
                                                apr_hash_this_key(hi),
                                                NULL /* value */,
                                                scratch_pool));
        }
    }

  /* Check for lock information. */

  /* This works around a bug in some older versions of mod_dav_svn in that it
   * will not send remove-prop in the update report when a lock property
   * disappears when send-all is false.

   ### Given that we only fetch props on additions, is this really necessary?
       Or is it covering up old local copy bugs where we copied locks to other
       paths? */
  if (!ctx->add_props_included
      && file->lock_token && !file->found_lock_prop
      && SVN_IS_VALID_REVNUM(file->base_rev) /* file_is_added */)
    {
      SVN_ERR(ctx->editor->change_file_prop(file->file_baton,
                                            SVN_PROP_ENTRY_LOCK_TOKEN,
                                            NULL,
                                            scratch_pool));
    }

  if (file->url)
    {
      SVN_ERR(ctx->editor->change_file_prop(file->file_baton,
                                            SVN_RA_SERF__WC_CHECKED_IN_URL,
                                            svn_string_create(file->url,
                                                              scratch_pool),
                                            scratch_pool));
    }

  /* Close the file via the editor. */
  SVN_ERR(ctx->editor->close_file(file->file_baton,
                                  svn_checksum_to_cstring(
                                        file->final_md5_checksum,
                                        scratch_pool),
                                  scratch_pool));

  svn_pool_destroy(file->pool);

  SVN_ERR(maybe_close_dir(parent_dir)); /* Remove reference */

  return SVN_NO_ERROR;
}