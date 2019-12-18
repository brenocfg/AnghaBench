#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_3__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_12__ {TYPE_2__* editor; } ;
typedef  TYPE_4__ report_context_t ;
struct TYPE_13__ {int /*<<< orphan*/  file_baton; scalar_t__ found_lock_prop; scalar_t__ lock_token; TYPE_1__* parent_dir; } ;
typedef  TYPE_5__ file_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_10__ {int /*<<< orphan*/  (* change_file_prop ) (int /*<<< orphan*/ ,char const*,TYPE_3__ const*,int /*<<< orphan*/ *) ;} ;
struct TYPE_9__ {TYPE_4__* ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  apr_collapse_spaces (char*,char*) ; 
 char* apr_pstrdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ensure_file_opened (TYPE_5__*,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char const*,TYPE_3__ const*,int /*<<< orphan*/ *) ; 
 char* svn_ra_serf__svnname_from_wirename (char const*,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
set_file_props(void *baton,
               const char *path,
               const char *ns,
               const char *name,
               const svn_string_t *val,
               apr_pool_t *scratch_pool)
{
  file_baton_t *file = baton;
  report_context_t *ctx = file->parent_dir->ctx;
  const char *prop_name;

  prop_name = svn_ra_serf__svnname_from_wirename(ns, name, scratch_pool);

  if (!prop_name)
    {
      /* This works around a bug in some older versions of
       * mod_dav_svn in that it will not send remove-prop in the update
       * report when a lock property disappears when send-all is false.
       *
       * Therefore, we'll try to look at our properties and see if there's
       * an active lock.  If not, then we'll assume there isn't a lock
       * anymore.
       */
      /* assert(!ctx->add_props_included); // Or we wouldn't be here */
      if (file->lock_token
          && !file->found_lock_prop
          && val
          && strcmp(ns, "DAV:") == 0
          && strcmp(name, "lockdiscovery") == 0)
        {
          char *new_lock;
          new_lock = apr_pstrdup(scratch_pool, val->data);
          apr_collapse_spaces(new_lock, new_lock);

          if (new_lock[0] != '\0')
            file->found_lock_prop = TRUE;
        }

      return SVN_NO_ERROR;
    }

  SVN_ERR(ensure_file_opened(file, scratch_pool));

  SVN_ERR(ctx->editor->change_file_prop(file->file_baton,
                                        prop_name, val,
                                        scratch_pool));

  return SVN_NO_ERROR;
}