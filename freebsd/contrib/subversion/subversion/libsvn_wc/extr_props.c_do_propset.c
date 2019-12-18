#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {char const* prop_name; scalar_t__ kind; } ;
typedef  TYPE_1__ svn_wc_notify_t ;
typedef  int /*<<< orphan*/  (* svn_wc_notify_func2_t ) (void*,TYPE_1__*,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  svn_wc_notify_action_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
struct TYPE_15__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_3__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_skel_t ;
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct getter_baton {char const* local_abspath; TYPE_3__* mime_type; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_W (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 char const* SVN_PROP_EOL_STYLE ; 
 char const* SVN_PROP_EXECUTABLE ; 
 char const* SVN_PROP_KEYWORDS ; 
 char const* SVN_PROP_MIME_TYPE ; 
 char const* SVN_PROP_NEEDS_LOCK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_file_for_validation ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  stub1 (void*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_is_absolute (char const*) ; 
 TYPE_3__* svn_hash_gets (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,char const*,TYPE_3__ const*) ; 
 scalar_t__ svn_node_file ; 
 scalar_t__ svn_prop_is_svn_prop (char const*) ; 
 int /*<<< orphan*/  svn_string_compare (TYPE_3__ const*,TYPE_3__*) ; 
 scalar_t__ svn_subst_keywords_differ2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_op_set_props (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_read_props (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__expand_keywords (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__wq_build_sync_file_flags (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__wq_run (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_canonicalize_svn_prop (TYPE_3__ const**,char const*,TYPE_3__ const*,char const*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct getter_baton*,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_wc_create_notify (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_notify_property_added ; 
 int /*<<< orphan*/  svn_wc_notify_property_deleted ; 
 int /*<<< orphan*/  svn_wc_notify_property_deleted_nonexistent ; 
 int /*<<< orphan*/  svn_wc_notify_property_modified ; 

__attribute__((used)) static svn_error_t *
do_propset(svn_wc__db_t *db,
           const char *local_abspath,
           svn_node_kind_t kind,
           const char *name,
           const svn_string_t *value,
           svn_boolean_t skip_checks,
           svn_wc_notify_func2_t notify_func,
           void *notify_baton,
           apr_pool_t *scratch_pool)
{
  apr_hash_t *prophash;
  svn_wc_notify_action_t notify_action;
  svn_skel_t *work_item = NULL;
  svn_boolean_t clear_recorded_info = FALSE;

  SVN_ERR_ASSERT(svn_dirent_is_absolute(local_abspath));

  SVN_ERR_W(svn_wc__db_read_props(&prophash, db, local_abspath,
                                  scratch_pool, scratch_pool),
            _("Failed to load current properties"));

  /* Setting an inappropriate property is not allowed (unless
     overridden by 'skip_checks', in some circumstances).  Deleting an
     inappropriate property is allowed, however, since older clients
     allowed (and other clients possibly still allow) setting it in
     the first place. */
  if (value && svn_prop_is_svn_prop(name))
    {
      const svn_string_t *new_value;
      struct getter_baton gb;

      gb.mime_type = svn_hash_gets(prophash, SVN_PROP_MIME_TYPE);
      gb.local_abspath = local_abspath;

      SVN_ERR(svn_wc_canonicalize_svn_prop(&new_value, name, value,
                                           local_abspath, kind,
                                           skip_checks,
                                           get_file_for_validation, &gb,
                                           scratch_pool));
      value = new_value;
    }

  if (kind == svn_node_file
        && (strcmp(name, SVN_PROP_EXECUTABLE) == 0
            || strcmp(name, SVN_PROP_NEEDS_LOCK) == 0))
    {
      SVN_ERR(svn_wc__wq_build_sync_file_flags(&work_item, db, local_abspath,
                                               scratch_pool, scratch_pool));
    }

  /* If we're changing this file's list of expanded keywords, then
   * we'll need to invalidate its text timestamp, since keyword
   * expansion affects the comparison of working file to text base.
   *
   * Here we retrieve the old list of expanded keywords; after the
   * property is set, we'll grab the new list and see if it differs
   * from the old one.
   */
  if (kind == svn_node_file && strcmp(name, SVN_PROP_KEYWORDS) == 0)
    {
      svn_string_t *old_value = svn_hash_gets(prophash, SVN_PROP_KEYWORDS);
      apr_hash_t *old_keywords, *new_keywords;

      if (old_value)
        SVN_ERR(svn_wc__expand_keywords(&old_keywords,
                                        db, local_abspath, NULL,
                                        old_value->data, TRUE,
                                        scratch_pool, scratch_pool));
      else
        old_keywords = apr_hash_make(scratch_pool);

      if (value)
        SVN_ERR(svn_wc__expand_keywords(&new_keywords,
                                        db, local_abspath, NULL,
                                        value->data, TRUE,
                                        scratch_pool, scratch_pool));
      else
        new_keywords = apr_hash_make(scratch_pool);

      if (svn_subst_keywords_differ2(old_keywords, new_keywords, FALSE,
                                     scratch_pool))
        {
          /* If the keywords have changed, then the translation of the file
             may be different. We should invalidate the RECORDED_SIZE
             and RECORDED_TIME on this node.

             Note that we don't immediately re-translate the file. But a
             "has it changed?" check in the future will do a translation
             from the pristine, and it will want to compare the (new)
             resulting RECORDED_SIZE against the working copy file.

             Also, when this file is (de)translated with the new keywords,
             then it could be different, relative to the pristine. We want
             to ensure the RECORDED_TIME is different, to indicate that
             a full detranslate/compare is performed.  */
          clear_recorded_info = TRUE;
        }
    }
  else if (kind == svn_node_file && strcmp(name, SVN_PROP_EOL_STYLE) == 0)
    {
      svn_string_t *old_value = svn_hash_gets(prophash, SVN_PROP_EOL_STYLE);

      if (((value == NULL) != (old_value == NULL))
          || (value && ! svn_string_compare(value, old_value)))
        {
          clear_recorded_info = TRUE;
        }
    }

  /* Find out what type of property change we are doing: add, modify, or
     delete. */
  if (svn_hash_gets(prophash, name) == NULL)
    {
      if (value == NULL)
        /* Deleting a non-existent property. */
        notify_action = svn_wc_notify_property_deleted_nonexistent;
      else
        /* Adding a property. */
        notify_action = svn_wc_notify_property_added;
    }
  else
    {
      if (value == NULL)
        /* Deleting the property. */
        notify_action = svn_wc_notify_property_deleted;
      else
        /* Modifying property. */
        notify_action = svn_wc_notify_property_modified;
    }

  /* Now we have all the properties in our hash.  Simply merge the new
     property into it. */
  svn_hash_sets(prophash, name, value);

  /* Drop it right into the db..  */
  SVN_ERR(svn_wc__db_op_set_props(db, local_abspath, prophash,
                                  clear_recorded_info, NULL, work_item,
                                  scratch_pool));

  /* Run our workqueue item for sync'ing flags with props. */
  if (work_item)
    SVN_ERR(svn_wc__wq_run(db, local_abspath, NULL, NULL, scratch_pool));

  if (notify_func)
    {
      svn_wc_notify_t *notify = svn_wc_create_notify(local_abspath,
                                                     notify_action,
                                                     scratch_pool);
      notify->prop_name = name;
      notify->kind = kind;

      (*notify_func)(notify_baton, notify, scratch_pool);
    }

  return SVN_NO_ERROR;
}