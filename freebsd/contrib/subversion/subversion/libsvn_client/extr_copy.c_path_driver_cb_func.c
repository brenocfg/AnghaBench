#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int svn_boolean_t ;
struct path_driver_cb_baton {TYPE_1__* editor; scalar_t__ is_move; int /*<<< orphan*/  action_hash; } ;
struct TYPE_5__ {scalar_t__ src_kind; scalar_t__ externals; scalar_t__ mergeinfo; int /*<<< orphan*/  src_revnum; int /*<<< orphan*/ * src_url; int /*<<< orphan*/  only_pin_externals; int /*<<< orphan*/  src_path; scalar_t__ resurrection; scalar_t__ dir_add; } ;
typedef  TYPE_2__ path_driver_info_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_4__ {int /*<<< orphan*/ * (* change_dir_prop ) (void*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ;int /*<<< orphan*/ * (* open_directory ) (char const*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ;int /*<<< orphan*/ * (* add_directory ) (char const*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ;int /*<<< orphan*/ * (* close_file ) (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/ * (* change_file_prop ) (void*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ;int /*<<< orphan*/ * (* add_file ) (char const*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ;int /*<<< orphan*/ * (* delete_entry ) (char const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_EXTERNALS ; 
 int /*<<< orphan*/  SVN_PROP_MERGEINFO ; 
 int TRUE ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * stub1 (char const*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/ * stub2 (char const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub3 (char const*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/ * stub4 (void*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub5 (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub6 (char const*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/ * stub7 (void*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub8 (char const*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/ * stub9 (void*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_hash_gets (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ svn_node_file ; 
 int /*<<< orphan*/ * svn_path_check_valid (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_path_is_empty (char const*) ; 

__attribute__((used)) static svn_error_t *
path_driver_cb_func(void **dir_baton,
                    void *parent_baton,
                    void *callback_baton,
                    const char *path,
                    apr_pool_t *pool)
{
  struct path_driver_cb_baton *cb_baton = callback_baton;
  svn_boolean_t do_delete = FALSE, do_add = FALSE;
  path_driver_info_t *path_info = svn_hash_gets(cb_baton->action_hash, path);

  /* Initialize return value. */
  *dir_baton = NULL;

  /* This function should never get an empty PATH.  We can neither
     create nor delete the empty PATH, so if someone is calling us
     with such, the code is just plain wrong. */
  SVN_ERR_ASSERT(! svn_path_is_empty(path));

  /* Check to see if we need to add the path as a parent directory. */
  if (path_info->dir_add)
    {
      return cb_baton->editor->add_directory(path, parent_baton, NULL,
                                             SVN_INVALID_REVNUM, pool,
                                             dir_baton);
    }

  /* If this is a resurrection, we know the source and dest paths are
     the same, and that our driver will only be calling us once.  */
  if (path_info->resurrection)
    {
      /* If this is a move, we do nothing.  Otherwise, we do the copy.  */
      if (! cb_baton->is_move)
        do_add = TRUE;
    }
  /* Not a resurrection. */
  else
    {
      /* If this is a move, we check PATH to see if it is the source
         or the destination of the move. */
      if (cb_baton->is_move)
        {
          if (strcmp(path_info->src_path, path) == 0)
            do_delete = TRUE;
          else
            do_add = TRUE;
        }
      /* Not a move?  This must just be the copy addition. */
      else
        {
          do_add = !path_info->only_pin_externals;
        }
    }

  if (do_delete)
    {
      SVN_ERR(cb_baton->editor->delete_entry(path, SVN_INVALID_REVNUM,
                                             parent_baton, pool));
    }
  if (do_add)
    {
      SVN_ERR(svn_path_check_valid(path, pool));

      if (path_info->src_kind == svn_node_file)
        {
          void *file_baton;
          SVN_ERR(cb_baton->editor->add_file(path, parent_baton,
                                             path_info->src_url,
                                             path_info->src_revnum,
                                             pool, &file_baton));
          if (path_info->mergeinfo)
            SVN_ERR(cb_baton->editor->change_file_prop(file_baton,
                                                       SVN_PROP_MERGEINFO,
                                                       path_info->mergeinfo,
                                                       pool));
          SVN_ERR(cb_baton->editor->close_file(file_baton, NULL, pool));
        }
      else
        {
          SVN_ERR(cb_baton->editor->add_directory(path, parent_baton,
                                                  path_info->src_url,
                                                  path_info->src_revnum,
                                                  pool, dir_baton));
          if (path_info->mergeinfo)
            SVN_ERR(cb_baton->editor->change_dir_prop(*dir_baton,
                                                      SVN_PROP_MERGEINFO,
                                                      path_info->mergeinfo,
                                                      pool));
        }
    }

  if (path_info->externals)
    {
      if (*dir_baton == NULL)
        SVN_ERR(cb_baton->editor->open_directory(path, parent_baton,
                                                 SVN_INVALID_REVNUM,
                                                 pool, dir_baton));

      SVN_ERR(cb_baton->editor->change_dir_prop(*dir_baton, SVN_PROP_EXTERNALS,
                                                path_info->externals, pool));
    }

  return SVN_NO_ERROR;
}