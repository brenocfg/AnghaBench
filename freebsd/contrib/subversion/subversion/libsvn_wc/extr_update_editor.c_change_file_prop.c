#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_string_t ;
struct TYPE_3__ {int /*<<< orphan*/  value; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ svn_prop_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  void* svn_boolean_t ;
struct file_baton {void* already_notified; void* add_existed; void* shadowed; int /*<<< orphan*/  local_abspath; int /*<<< orphan*/  edit_conflict; int /*<<< orphan*/  pool; int /*<<< orphan*/  new_repos_relpath; int /*<<< orphan*/  old_revision; int /*<<< orphan*/  old_repos_relpath; struct edit_baton* edit_baton; scalar_t__ local_prop_mods; scalar_t__ adding_file; int /*<<< orphan*/  edited; int /*<<< orphan*/  propchanges; scalar_t__ skip_this; } ;
struct edit_baton {int /*<<< orphan*/  db; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_SPECIAL ; 
 void* TRUE ; 
 TYPE_1__* apr_array_push (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  complete_conflict (int /*<<< orphan*/ ,struct edit_baton*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_notification (struct edit_baton*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mark_file_edited (struct file_baton*,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_hash_gets (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_node_file ; 
 scalar_t__ svn_prop_regular_kind ; 
 scalar_t__ svn_property_kind2 (char const*) ; 
 int /*<<< orphan*/  svn_string_dup (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 void* svn_tristate_false ; 
 void* svn_tristate_true ; 
 int /*<<< orphan*/  svn_wc__conflict_skel_add_tree_conflict (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__conflict_skel_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_wc__db_base_get_props (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_op_make_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__internal_file_modified_p (void**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_conflict_action_replace ; 
 int /*<<< orphan*/  svn_wc_conflict_reason_edited ; 
 int /*<<< orphan*/  svn_wc_notify_tree_conflict ; 

__attribute__((used)) static svn_error_t *
change_file_prop(void *file_baton,
                 const char *name,
                 const svn_string_t *value,
                 apr_pool_t *scratch_pool)
{
  struct file_baton *fb = file_baton;
  svn_prop_t *propchange;

  if (fb->skip_this)
    return SVN_NO_ERROR;

  /* Push a new propchange to the file baton's array of propchanges */
  propchange = apr_array_push(fb->propchanges);
  propchange->name = apr_pstrdup(fb->pool, name);
  propchange->value = svn_string_dup(value, fb->pool);

  if (!fb->edited && svn_property_kind2(name) == svn_prop_regular_kind)
    SVN_ERR(mark_file_edited(fb, scratch_pool));

  if (! fb->shadowed
      && strcmp(name, SVN_PROP_SPECIAL) == 0)
    {
      struct edit_baton *eb = fb->edit_baton;
      svn_boolean_t modified = FALSE;
      svn_boolean_t becomes_symlink;
      svn_boolean_t was_symlink;

      /* Let's see if we have a change as in some scenarios servers report
         non-changes of properties. */
      becomes_symlink = (value != NULL);

      if (fb->adding_file)
        was_symlink = becomes_symlink; /* No change */
      else
        {
          apr_hash_t *props;

          /* We read the server-props, not the ACTUAL props here as we just
             want to see if this is really an incoming prop change. */
          SVN_ERR(svn_wc__db_base_get_props(&props, eb->db,
                                            fb->local_abspath,
                                            scratch_pool, scratch_pool));

          was_symlink = ((props
                              && svn_hash_gets(props, SVN_PROP_SPECIAL) != NULL)
                              ? svn_tristate_true
                              : svn_tristate_false);
        }

      if (was_symlink != becomes_symlink)
        {
          /* If the local node was not modified, we continue as usual, if
             modified we want a tree conflict just like how we would handle
             it when receiving a delete + add (aka "replace") */
          if (fb->local_prop_mods)
            modified = TRUE;
          else
            SVN_ERR(svn_wc__internal_file_modified_p(&modified, eb->db,
                                                     fb->local_abspath,
                                                     FALSE, scratch_pool));
        }

      if (modified)
        {
          if (!fb->edit_conflict)
            fb->edit_conflict = svn_wc__conflict_skel_create(fb->pool);

          SVN_ERR(svn_wc__conflict_skel_add_tree_conflict(
                                     fb->edit_conflict,
                                     eb->db, fb->local_abspath,
                                     svn_wc_conflict_reason_edited,
                                     svn_wc_conflict_action_replace,
                                     NULL,
                                     fb->pool, scratch_pool));

          SVN_ERR(complete_conflict(fb->edit_conflict, fb->edit_baton,
                                    fb->local_abspath, fb->old_repos_relpath,
                                    fb->old_revision, fb->new_repos_relpath,
                                    svn_node_file, svn_node_file,
                                    NULL, fb->pool, scratch_pool));

          /* Create a copy of the existing (pre update) BASE node in WORKING,
             mark a tree conflict and handle the rest of the update as
             shadowed */
          SVN_ERR(svn_wc__db_op_make_copy(eb->db, fb->local_abspath,
                                          fb->edit_conflict, NULL,
                                          scratch_pool));

          do_notification(eb, fb->local_abspath, svn_node_file,
                          svn_wc_notify_tree_conflict, scratch_pool);

          /* Ok, we introduced a replacement, so we can now handle the rest
             as a normal shadowed update */
          fb->shadowed = TRUE;
          fb->add_existed = FALSE;
          fb->already_notified = TRUE;
      }
    }

  return SVN_NO_ERROR;
}