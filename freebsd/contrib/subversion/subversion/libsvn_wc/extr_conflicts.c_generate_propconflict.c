#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_wc_operation_t ;
typedef  int /*<<< orphan*/  svn_wc_conflict_version_t ;
struct TYPE_23__ {int choice; void* merged_file; TYPE_5__* merged_value; } ;
typedef  TYPE_1__ svn_wc_conflict_result_t ;
typedef  int /*<<< orphan*/  (* svn_wc_conflict_resolver_func2_t ) (TYPE_1__**,TYPE_3__*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;
struct TYPE_24__ {void* merged_file; int /*<<< orphan*/  reason; int /*<<< orphan*/  action; int /*<<< orphan*/  prop_reject_abspath; int /*<<< orphan*/  their_abspath; TYPE_5__ const* prop_value_incoming_old; TYPE_5__ const* prop_value_base; void* base_abspath; TYPE_5__ const* prop_value_incoming_new; TYPE_5__ const* prop_value_working; void* my_abspath; int /*<<< orphan*/  const* src_right_version; int /*<<< orphan*/  const* src_left_version; int /*<<< orphan*/  operation; } ;
typedef  TYPE_3__ svn_wc_conflict_description2_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  int /*<<< orphan*/  svn_stringbuf_t ;
struct TYPE_25__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_5__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_diff_t ;
typedef  int /*<<< orphan*/  svn_diff_file_options_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_WC_CONFLICT_RESOLVER_FAILURE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  svn_diff_conflict_display_modified_latest ; 
 int /*<<< orphan*/ * svn_diff_file_options_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_diff_mem_string_diff3 (int /*<<< orphan*/ **,TYPE_5__ const*,TYPE_5__ const*,TYPE_5__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_diff_mem_string_output_merge3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_5__ const*,TYPE_5__ const*,TYPE_5__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 char* svn_dirent_dirname (char const*,int /*<<< orphan*/ *) ; 
 void* svn_dirent_join (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,char const*,TYPE_5__ const*) ; 
 int /*<<< orphan*/  svn_io_file_del_on_pool_cleanup ; 
 int /*<<< orphan*/  svn_io_write_unique (char const**,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_open_unique (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_string_compare (TYPE_5__ const*,TYPE_5__ const*) ; 
 TYPE_5__* svn_stringbuf__morph_into_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stringbuf_from_file2 (int /*<<< orphan*/ **,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_op_set_props (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_read_props (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_conflict_action_add ; 
 int /*<<< orphan*/  svn_wc_conflict_action_delete ; 
 int /*<<< orphan*/  svn_wc_conflict_action_edit ; 
#define  svn_wc_conflict_choose_base 132 
#define  svn_wc_conflict_choose_merged 131 
#define  svn_wc_conflict_choose_mine_full 130 
#define  svn_wc_conflict_choose_postpone 129 
#define  svn_wc_conflict_choose_theirs_full 128 
 TYPE_3__* svn_wc_conflict_description_create_prop2 (char const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_conflict_reason_deleted ; 
 int /*<<< orphan*/  svn_wc_conflict_reason_edited ; 
 int /*<<< orphan*/  svn_wc_conflict_reason_obstructed ; 

__attribute__((used)) static svn_error_t *
generate_propconflict(svn_boolean_t *conflict_remains,
                      svn_wc__db_t *db,
                      const char *local_abspath,
                      svn_node_kind_t kind,
                      svn_wc_operation_t operation,
                      const svn_wc_conflict_version_t *left_version,
                      const svn_wc_conflict_version_t *right_version,
                      const char *propname,
                      const svn_string_t *base_val,
                      const svn_string_t *working_val,
                      const svn_string_t *incoming_old_val,
                      const svn_string_t *incoming_new_val,
                      svn_wc_conflict_resolver_func2_t conflict_func,
                      void *conflict_baton,
                      svn_cancel_func_t cancel_func,
                      void *cancel_baton,
                      apr_pool_t *scratch_pool)
{
  svn_wc_conflict_result_t *result = NULL;
  svn_wc_conflict_description2_t *cdesc;
  const char *dirpath = svn_dirent_dirname(local_abspath, scratch_pool);
  const svn_string_t *new_value = NULL;

  cdesc = svn_wc_conflict_description_create_prop2(
                local_abspath,
                kind,
                propname, scratch_pool);

  cdesc->operation = operation;
  cdesc->src_left_version = left_version;
  cdesc->src_right_version = right_version;

  /* Create a tmpfile for each of the string_t's we've got.  */
  if (working_val)
    {
      const char *file_name;

      SVN_ERR(svn_io_write_unique(&file_name, dirpath, working_val->data,
                                  working_val->len,
                                  svn_io_file_del_on_pool_cleanup,
                                  scratch_pool));
      cdesc->my_abspath = svn_dirent_join(dirpath, file_name, scratch_pool);
      cdesc->prop_value_working = working_val;
    }

  if (incoming_new_val)
    {
      const char *file_name;

      SVN_ERR(svn_io_write_unique(&file_name, dirpath, incoming_new_val->data,
                                  incoming_new_val->len,
                                  svn_io_file_del_on_pool_cleanup,
                                  scratch_pool));

      /* ### For property conflicts, cd2 stores prop_reject_abspath in
       * ### their_abspath, and stores theirs_abspath in merged_file. */
      cdesc->merged_file = svn_dirent_join(dirpath, file_name, scratch_pool);
      cdesc->prop_value_incoming_new = incoming_new_val;
    }

  if (!base_val && !incoming_old_val)
    {
      /* If base and old are both NULL, then that's fine, we just let
         base_file stay NULL as-is.  Both agents are attempting to add a
         new property.  */
    }
  else if ((base_val && !incoming_old_val)
           || (!base_val && incoming_old_val))
    {
      /* If only one of base and old are defined, then we've got a
         situation where one agent is attempting to add the property
         for the first time, and the other agent is changing a
         property it thinks already exists.  In this case, we return
         whichever older-value happens to be defined, so that the
         conflict-callback can still attempt a 3-way merge. */

      const svn_string_t *conflict_base_val = base_val ? base_val
                                                       : incoming_old_val;
      const char *file_name;

      SVN_ERR(svn_io_write_unique(&file_name, dirpath,
                                  conflict_base_val->data,
                                  conflict_base_val->len,
                                  svn_io_file_del_on_pool_cleanup,
                                  scratch_pool));
      cdesc->base_abspath = svn_dirent_join(dirpath, file_name, scratch_pool);
    }
  else  /* base and old are both non-NULL */
    {
      const svn_string_t *conflict_base_val;
      const char *file_name;

      if (! svn_string_compare(base_val, incoming_old_val))
        {
          /* What happens if 'base' and 'old' don't match up?  In an
             ideal situation, they would.  But if they don't, this is
             a classic example of a patch 'hunk' failing to apply due
             to a lack of context.  For example: imagine that the user
             is busy changing the property from a value of "cat" to
             "dog", but the incoming propchange wants to change the
             same property value from "red" to "green".  Total context
             mismatch.

             HOWEVER: we can still pass one of the two base values as
             'base_file' to the callback anyway.  It's still useful to
             present the working and new values to the user to
             compare. */

          if (working_val && svn_string_compare(base_val, working_val))
            conflict_base_val = incoming_old_val;
          else
            conflict_base_val = base_val;
        }
      else
        {
          conflict_base_val = base_val;
        }

      SVN_ERR(svn_io_write_unique(&file_name, dirpath, conflict_base_val->data,
                                  conflict_base_val->len,
                                  svn_io_file_del_on_pool_cleanup, scratch_pool));
      cdesc->base_abspath = svn_dirent_join(dirpath, file_name, scratch_pool);

      cdesc->prop_value_base = base_val;
      cdesc->prop_value_incoming_old = incoming_old_val;

      if (working_val && incoming_new_val)
        {
          svn_stream_t *mergestream;
          svn_diff_t *diff;
          svn_diff_file_options_t *options =
            svn_diff_file_options_create(scratch_pool);

          SVN_ERR(svn_stream_open_unique(&mergestream, &cdesc->prop_reject_abspath,
                                         NULL, svn_io_file_del_on_pool_cleanup,
                                         scratch_pool, scratch_pool));
          SVN_ERR(svn_diff_mem_string_diff3(&diff, conflict_base_val,
                                            working_val,
                                            incoming_new_val, options, scratch_pool));
          SVN_ERR(svn_diff_mem_string_output_merge3(mergestream, diff,
                   conflict_base_val, working_val,
                   incoming_new_val, NULL, NULL, NULL, NULL,
                   svn_diff_conflict_display_modified_latest,
                   cancel_func, cancel_baton, scratch_pool));
          SVN_ERR(svn_stream_close(mergestream));

          /* ### For property conflicts, cd2 stores prop_reject_abspath in
           * ### their_abspath, and stores theirs_abspath in merged_file. */
          cdesc->their_abspath = cdesc->prop_reject_abspath;
        }
    }

  if (!incoming_old_val && incoming_new_val)
    cdesc->action = svn_wc_conflict_action_add;
  else if (incoming_old_val && !incoming_new_val)
    cdesc->action = svn_wc_conflict_action_delete;
  else
    cdesc->action = svn_wc_conflict_action_edit;

  if (base_val && !working_val)
    cdesc->reason = svn_wc_conflict_reason_deleted;
  else if (!base_val && working_val)
    cdesc->reason = svn_wc_conflict_reason_obstructed;
  else
    cdesc->reason = svn_wc_conflict_reason_edited;

  /* Invoke the interactive conflict callback. */
  SVN_ERR(conflict_func(&result, cdesc, conflict_baton, scratch_pool,
                        scratch_pool));
  if (result == NULL)
    {
      *conflict_remains = TRUE;
      return svn_error_create(SVN_ERR_WC_CONFLICT_RESOLVER_FAILURE,
                              NULL, _("Conflict callback violated API:"
                                      " returned no results"));
    }


  switch (result->choice)
    {
      default:
      case svn_wc_conflict_choose_postpone:
        {
          *conflict_remains = TRUE;
          break;
        }
      case svn_wc_conflict_choose_mine_full:
        {
          /* No need to change actual_props; it already contains working_val */
          *conflict_remains = FALSE;
          new_value = working_val;
          break;
        }
      /* I think _mine_full and _theirs_full are appropriate for prop
         behavior as well as the text behavior.  There should even be
         analogous behaviors for _mine and _theirs when those are
         ready, namely: fold in all non-conflicting prop changes, and
         then choose _mine side or _theirs side for conflicting ones. */
      case svn_wc_conflict_choose_theirs_full:
        {
          *conflict_remains = FALSE;
          new_value = incoming_new_val;
          break;
        }
      case svn_wc_conflict_choose_base:
        {
          *conflict_remains = FALSE;
          new_value = base_val;
          break;
        }
      case svn_wc_conflict_choose_merged:
        {
          if (!cdesc->merged_file 
              && (!result->merged_file && !result->merged_value))
            return svn_error_create
                (SVN_ERR_WC_CONFLICT_RESOLVER_FAILURE,
                 NULL, _("Conflict callback violated API:"
                         " returned no merged file"));

          if (result->merged_value)
            new_value = result->merged_value;
          else
            {
              svn_stringbuf_t *merged_stringbuf;

              SVN_ERR(svn_stringbuf_from_file2(&merged_stringbuf,
                                               result->merged_file ?
                                                    result->merged_file :
                                                    cdesc->merged_file,
                                               scratch_pool));
              new_value = svn_stringbuf__morph_into_string(merged_stringbuf);
            }
          *conflict_remains = FALSE;
          break;
        }
    }

  if (!*conflict_remains)
    {
      apr_hash_t *props;

      /* For now, just set the property values. This should really do some of the
         more advanced things from svn_wc_prop_set() */

      SVN_ERR(svn_wc__db_read_props(&props, db, local_abspath, scratch_pool,
                                    scratch_pool));

      svn_hash_sets(props, propname, new_value);

      SVN_ERR(svn_wc__db_op_set_props(db, local_abspath, props,
                                      FALSE, NULL, NULL,
                                      scratch_pool));
    }

  return SVN_NO_ERROR;
}