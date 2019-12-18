#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char const* name; char const* checksum; char const* cmt_author; char* cachable_props; char* present_props; char const* prejfile; char const* conflict_old; char const* conflict_new; char const* conflict_wrk; char const* uuid; char const* lock_token; char const* lock_owner; char const* lock_comment; char const* changelist; char const* tree_conflict_data; int /*<<< orphan*/  file_external_rev; int /*<<< orphan*/  file_external_peg_rev; int /*<<< orphan*/  file_external_path; int /*<<< orphan*/  depth; scalar_t__ working_size; int /*<<< orphan*/  keep_local; int /*<<< orphan*/  lock_creation_date; int /*<<< orphan*/  incomplete; int /*<<< orphan*/  absent; int /*<<< orphan*/  deleted; int /*<<< orphan*/  copyfrom_rev; scalar_t__ copyfrom_url; int /*<<< orphan*/  copied; void* has_prop_mods; void* has_props; int /*<<< orphan*/  cmt_rev; int /*<<< orphan*/  cmt_date; int /*<<< orphan*/  text_time; int /*<<< orphan*/  schedule; scalar_t__ url; scalar_t__ repos; int /*<<< orphan*/  revision; int /*<<< orphan*/  kind; } ;
typedef  TYPE_1__ svn_wc_entry_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  scalar_t__ apr_off_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENTRIES_BOOL_ABSENT ; 
 int /*<<< orphan*/  ENTRIES_BOOL_COPIED ; 
 int /*<<< orphan*/  ENTRIES_BOOL_DELETED ; 
 int /*<<< orphan*/  ENTRIES_BOOL_INCOMPLETE ; 
 int /*<<< orphan*/  ENTRIES_BOOL_KEEP_LOCAL ; 
 int /*<<< orphan*/  ENTRIES_VALUE_ADD ; 
 int /*<<< orphan*/  ENTRIES_VALUE_DELETE ; 
 int /*<<< orphan*/  ENTRIES_VALUE_DIR ; 
 int /*<<< orphan*/  ENTRIES_VALUE_FILE ; 
 int /*<<< orphan*/  ENTRIES_VALUE_REPLACE ; 
 void* FALSE ; 
 int /*<<< orphan*/  MAYBE_DONE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ENTRY_ATTRIBUTE_INVALID ; 
 int /*<<< orphan*/  SVN_ERR_NODE_UNKNOWN_KIND ; 
 int /*<<< orphan*/  SVN_ERR_WC_CORRUPT ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 char const* SVN_WC_ENTRY_THIS_DIR ; 
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_1__* alloc_entry (int /*<<< orphan*/ *) ; 
 scalar_t__ apr_strtoi64 (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_bool (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**,char const*) ; 
 int /*<<< orphan*/  read_path (char const**,char**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_revnum (int /*<<< orphan*/ *,char**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_str (char const**,char**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_time (int /*<<< orphan*/ *,char**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_url (scalar_t__*,char**,char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_val (char const**,char**,char const*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_depth_exclude ; 
 int /*<<< orphan*/  svn_depth_from_word (char const*) ; 
 int /*<<< orphan*/  svn_depth_infinity ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_node_dir ; 
 int /*<<< orphan*/  svn_node_file ; 
 int /*<<< orphan*/  svn_node_none ; 
 int /*<<< orphan*/  svn_uri__is_ancestor (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  svn_wc__unserialize_file_external (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_schedule_add ; 
 int /*<<< orphan*/  svn_wc_schedule_delete ; 
 int /*<<< orphan*/  svn_wc_schedule_normal ; 
 int /*<<< orphan*/  svn_wc_schedule_replace ; 

__attribute__((used)) static svn_error_t *
read_entry(svn_wc_entry_t **new_entry,
           char **buf, const char *end,
           int entries_format,
           apr_pool_t *pool)
{
  svn_wc_entry_t *entry = alloc_entry(pool);
  const char *name;

#define MAYBE_DONE if (**buf == '\f') goto done

  /* Find the name and set up the entry under that name. */
  SVN_ERR(read_path(&name, buf, end, pool));
  entry->name = name ? name : SVN_WC_ENTRY_THIS_DIR;

  /* Set up kind. */
  {
    const char *kindstr;
    SVN_ERR(read_val(&kindstr, buf, end));
    if (kindstr)
      {
        if (strcmp(kindstr, ENTRIES_VALUE_FILE) == 0)
          entry->kind = svn_node_file;
        else if (strcmp(kindstr, ENTRIES_VALUE_DIR) == 0)
          entry->kind = svn_node_dir;
        else
          return svn_error_createf
            (SVN_ERR_NODE_UNKNOWN_KIND, NULL,
             _("Entry '%s' has invalid node kind"),
             (name ? name : SVN_WC_ENTRY_THIS_DIR));
      }
    else
      entry->kind = svn_node_none;
  }
  MAYBE_DONE;

  /* Attempt to set revision (resolve_to_defaults may do it later, too) */
  SVN_ERR(read_revnum(&entry->revision, buf, end, pool));
  MAYBE_DONE;

  /* Attempt to set up url path (again, see resolve_to_defaults). */
  SVN_ERR(read_url(&entry->url, buf, end, entries_format, pool));
  MAYBE_DONE;

  /* Set up repository root.  Make sure it is a prefix of url. */
  SVN_ERR(read_url(&entry->repos, buf, end, entries_format, pool));
  if (entry->repos && entry->url
      && ! svn_uri__is_ancestor(entry->repos, entry->url))
    return svn_error_createf(SVN_ERR_WC_CORRUPT, NULL,
                             _("Entry for '%s' has invalid repository "
                               "root"),
                             name ? name : SVN_WC_ENTRY_THIS_DIR);
  MAYBE_DONE;

  /* Look for a schedule attribute on this entry. */
  {
    const char *schedulestr;
    SVN_ERR(read_val(&schedulestr, buf, end));
    entry->schedule = svn_wc_schedule_normal;
    if (schedulestr)
      {
        if (strcmp(schedulestr, ENTRIES_VALUE_ADD) == 0)
          entry->schedule = svn_wc_schedule_add;
        else if (strcmp(schedulestr, ENTRIES_VALUE_DELETE) == 0)
          entry->schedule = svn_wc_schedule_delete;
        else if (strcmp(schedulestr, ENTRIES_VALUE_REPLACE) == 0)
          entry->schedule = svn_wc_schedule_replace;
        else
          return svn_error_createf(
            SVN_ERR_ENTRY_ATTRIBUTE_INVALID, NULL,
            _("Entry '%s' has invalid 'schedule' value"),
            name ? name : SVN_WC_ENTRY_THIS_DIR);
      }
  }
  MAYBE_DONE;

  /* Attempt to set up text timestamp. */
  SVN_ERR(read_time(&entry->text_time, buf, end, pool));
  MAYBE_DONE;

  /* Checksum. */
  SVN_ERR(read_str(&entry->checksum, buf, end, pool));
  MAYBE_DONE;

  /* Setup last-committed values. */
  SVN_ERR(read_time(&entry->cmt_date, buf, end, pool));
  MAYBE_DONE;

  SVN_ERR(read_revnum(&entry->cmt_rev, buf, end, pool));
  MAYBE_DONE;

  SVN_ERR(read_str(&entry->cmt_author, buf, end, pool));
  MAYBE_DONE;

  /* has-props, has-prop-mods, cachable-props, present-props are all
     deprecated. Read any values that may be in the 'entries' file, but
     discard them, and just put default values into the entry. */
  {
    const char *unused_value;

    /* has-props flag. */
    SVN_ERR(read_val(&unused_value, buf, end));
    entry->has_props = FALSE;
    MAYBE_DONE;

    /* has-prop-mods flag. */
    SVN_ERR(read_val(&unused_value, buf, end));
    entry->has_prop_mods = FALSE;
    MAYBE_DONE;

    /* Use the empty string for cachable_props, indicating that we no
       longer attempt to cache any properties. An empty string for
       present_props means that no cachable props are present. */

    /* cachable-props string. */
    SVN_ERR(read_val(&unused_value, buf, end));
    entry->cachable_props = "";
    MAYBE_DONE;

    /* present-props string. */
    SVN_ERR(read_val(&unused_value, buf, end));
    entry->present_props = "";
    MAYBE_DONE;
  }

  /* Is this entry in a state of mental torment (conflict)? */
  {
    SVN_ERR(read_path(&entry->prejfile, buf, end, pool));
    MAYBE_DONE;
    SVN_ERR(read_path(&entry->conflict_old, buf, end, pool));
    MAYBE_DONE;
    SVN_ERR(read_path(&entry->conflict_new, buf, end, pool));
    MAYBE_DONE;
    SVN_ERR(read_path(&entry->conflict_wrk, buf, end, pool));
    MAYBE_DONE;
  }

  /* Is this entry copied? */
  SVN_ERR(read_bool(&entry->copied, ENTRIES_BOOL_COPIED, buf, end));
  MAYBE_DONE;

  SVN_ERR(read_url(&entry->copyfrom_url, buf, end, entries_format, pool));
  MAYBE_DONE;
  SVN_ERR(read_revnum(&entry->copyfrom_rev, buf, end, pool));
  MAYBE_DONE;

  /* Is this entry deleted? */
  SVN_ERR(read_bool(&entry->deleted, ENTRIES_BOOL_DELETED, buf, end));
  MAYBE_DONE;

  /* Is this entry absent? */
  SVN_ERR(read_bool(&entry->absent, ENTRIES_BOOL_ABSENT, buf, end));
  MAYBE_DONE;

  /* Is this entry incomplete? */
  SVN_ERR(read_bool(&entry->incomplete, ENTRIES_BOOL_INCOMPLETE, buf, end));
  MAYBE_DONE;

  /* UUID. */
  SVN_ERR(read_str(&entry->uuid, buf, end, pool));
  MAYBE_DONE;

  /* Lock token. */
  SVN_ERR(read_str(&entry->lock_token, buf, end, pool));
  MAYBE_DONE;

  /* Lock owner. */
  SVN_ERR(read_str(&entry->lock_owner, buf, end, pool));
  MAYBE_DONE;

  /* Lock comment. */
  SVN_ERR(read_str(&entry->lock_comment, buf, end, pool));
  MAYBE_DONE;

  /* Lock creation date. */
  SVN_ERR(read_time(&entry->lock_creation_date, buf, end, pool));
  MAYBE_DONE;

  /* Changelist. */
  SVN_ERR(read_str(&entry->changelist, buf, end, pool));
  MAYBE_DONE;

  /* Keep entry in working copy after deletion? */
  SVN_ERR(read_bool(&entry->keep_local, ENTRIES_BOOL_KEEP_LOCAL, buf, end));
  MAYBE_DONE;

  /* Translated size */
  {
    const char *val;

    /* read_val() returns NULL on an empty (e.g. default) entry line,
       and entry has already been initialized accordingly already */
    SVN_ERR(read_val(&val, buf, end));
    if (val)
      entry->working_size = (apr_off_t)apr_strtoi64(val, NULL, 0);
  }
  MAYBE_DONE;

  /* Depth. */
  {
    const char *result;
    SVN_ERR(read_val(&result, buf, end));
    if (result)
      {
        svn_boolean_t invalid;
        svn_boolean_t is_this_dir;

        entry->depth = svn_depth_from_word(result);

        /* Verify the depth value:
           THIS_DIR should not have an excluded value and SUB_DIR should only
           have excluded value. Remember that infinity value is not stored and
           should not show up here. Otherwise, something bad may have
           happened. However, infinity value itself will always be okay. */
        is_this_dir = !name;
        /* '!=': XOR */
        invalid = is_this_dir != (entry->depth != svn_depth_exclude);
        if (entry->depth != svn_depth_infinity && invalid)
          return svn_error_createf(
            SVN_ERR_ENTRY_ATTRIBUTE_INVALID, NULL,
            _("Entry '%s' has invalid 'depth' value"),
            name ? name : SVN_WC_ENTRY_THIS_DIR);
      }
    else
      entry->depth = svn_depth_infinity;

  }
  MAYBE_DONE;

  /* Tree conflict data. */
  SVN_ERR(read_str(&entry->tree_conflict_data, buf, end, pool));
  MAYBE_DONE;

  /* File external URL and revision. */
  {
    const char *str;
    SVN_ERR(read_str(&str, buf, end, pool));
    SVN_ERR(svn_wc__unserialize_file_external(&entry->file_external_path,
                                              &entry->file_external_peg_rev,
                                              &entry->file_external_rev,
                                              str,
                                              pool));
  }
  MAYBE_DONE;

 done:
  *new_entry = entry;
  return SVN_NO_ERROR;
}