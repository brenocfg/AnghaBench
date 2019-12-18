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
struct TYPE_4__ {char const* name; scalar_t__ working_size; scalar_t__ lock_creation_date; void* lock_comment; void* lock_owner; void* lock_token; void* cmt_author; void* cmt_rev; scalar_t__ cmt_date; void* uuid; void* checksum; scalar_t__ text_time; int /*<<< orphan*/  incomplete; int /*<<< orphan*/  absent; int /*<<< orphan*/  deleted; void* copyfrom_rev; void* copyfrom_url; int /*<<< orphan*/  copied; void* conflict_wrk; void* conflict_new; void* conflict_old; void* prejfile; void* schedule; int /*<<< orphan*/  kind; void* url; void* repos; void* revision; } ;
typedef  TYPE_1__ svn_wc_entry_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  scalar_t__ apr_off_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENTRIES_ATTR_ABSENT ; 
 int /*<<< orphan*/  ENTRIES_ATTR_CHECKSUM ; 
 int /*<<< orphan*/  ENTRIES_ATTR_CMT_AUTHOR ; 
 int /*<<< orphan*/  ENTRIES_ATTR_CMT_DATE ; 
 int /*<<< orphan*/  ENTRIES_ATTR_CMT_REV ; 
 int /*<<< orphan*/  ENTRIES_ATTR_CONFLICT_NEW ; 
 int /*<<< orphan*/  ENTRIES_ATTR_CONFLICT_OLD ; 
 int /*<<< orphan*/  ENTRIES_ATTR_CONFLICT_WRK ; 
 int /*<<< orphan*/  ENTRIES_ATTR_COPIED ; 
 int /*<<< orphan*/  ENTRIES_ATTR_COPYFROM_REV ; 
 int /*<<< orphan*/  ENTRIES_ATTR_COPYFROM_URL ; 
 int /*<<< orphan*/  ENTRIES_ATTR_DELETED ; 
 int /*<<< orphan*/  ENTRIES_ATTR_INCOMPLETE ; 
 int /*<<< orphan*/  ENTRIES_ATTR_KIND ; 
 int /*<<< orphan*/  ENTRIES_ATTR_LOCK_COMMENT ; 
 int /*<<< orphan*/  ENTRIES_ATTR_LOCK_CREATION_DATE ; 
 int /*<<< orphan*/  ENTRIES_ATTR_LOCK_OWNER ; 
 int /*<<< orphan*/  ENTRIES_ATTR_LOCK_TOKEN ; 
 int /*<<< orphan*/  ENTRIES_ATTR_NAME ; 
 int /*<<< orphan*/  ENTRIES_ATTR_PREJFILE ; 
 int /*<<< orphan*/  ENTRIES_ATTR_REPOS ; 
 int /*<<< orphan*/  ENTRIES_ATTR_REVISION ; 
 int /*<<< orphan*/  ENTRIES_ATTR_SCHEDULE ; 
 int /*<<< orphan*/  ENTRIES_ATTR_TEXT_TIME ; 
 int /*<<< orphan*/  ENTRIES_ATTR_URL ; 
 int /*<<< orphan*/  ENTRIES_ATTR_UUID ; 
 int /*<<< orphan*/  ENTRIES_ATTR_WORKING_SIZE ; 
 char* ENTRIES_VALUE_ADD ; 
 char* ENTRIES_VALUE_DELETE ; 
 char* ENTRIES_VALUE_DIR ; 
 char* ENTRIES_VALUE_FILE ; 
 char* ENTRIES_VALUE_REPLACE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ENTRY_ATTRIBUTE_INVALID ; 
 int /*<<< orphan*/  SVN_ERR_NODE_UNKNOWN_KIND ; 
 int /*<<< orphan*/  SVN_ERR_WC_CORRUPT ; 
 void* SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 void* SVN_STR_TO_REV (char const*) ; 
 char const* SVN_WC_ENTRY_THIS_DIR ; 
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_1__* alloc_entry (int /*<<< orphan*/ *) ; 
 char const* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ apr_strtoi64 (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_bool_attr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 void* extract_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* extract_string_normalize (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 char* svn_hash_gets (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_node_dir ; 
 int /*<<< orphan*/  svn_node_file ; 
 int /*<<< orphan*/  svn_node_none ; 
 int /*<<< orphan*/  svn_time_from_cstring (scalar_t__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_uri__is_ancestor (void*,void*) ; 
 void* svn_uri_canonicalize (void*,int /*<<< orphan*/ *) ; 
 void* svn_wc_schedule_add ; 
 void* svn_wc_schedule_delete ; 
 void* svn_wc_schedule_normal ; 
 void* svn_wc_schedule_replace ; 

__attribute__((used)) static svn_error_t *
atts_to_entry(svn_wc_entry_t **new_entry,
              apr_hash_t *atts,
              apr_pool_t *pool)
{
  svn_wc_entry_t *entry = alloc_entry(pool);
  const char *name;

  /* Find the name and set up the entry under that name. */
  name = svn_hash_gets(atts, ENTRIES_ATTR_NAME);
  entry->name = name ? apr_pstrdup(pool, name) : SVN_WC_ENTRY_THIS_DIR;

  /* Attempt to set revision (resolve_to_defaults may do it later, too)

     ### not used by loggy; no need to set MODIFY_FLAGS  */
  {
    const char *revision_str
      = svn_hash_gets(atts, ENTRIES_ATTR_REVISION);

    if (revision_str)
      entry->revision = SVN_STR_TO_REV(revision_str);
    else
      entry->revision = SVN_INVALID_REVNUM;
  }

  /* Attempt to set up url path (again, see resolve_to_defaults).

     ### not used by loggy; no need to set MODIFY_FLAGS  */
  entry->url = extract_string(atts, ENTRIES_ATTR_URL, pool);
  if (entry->url)
    entry->url = svn_uri_canonicalize(entry->url, pool);

  /* Set up repository root.  Make sure it is a prefix of url.

     ### not used by loggy; no need to set MODIFY_FLAGS  */
  entry->repos = extract_string(atts, ENTRIES_ATTR_REPOS, pool);
  if (entry->repos)
    entry->repos = svn_uri_canonicalize(entry->repos, pool);

  if (entry->url && entry->repos
      && !svn_uri__is_ancestor(entry->repos, entry->url))
    return svn_error_createf(SVN_ERR_WC_CORRUPT, NULL,
                             _("Entry for '%s' has invalid repository "
                               "root"),
                             name ? name : SVN_WC_ENTRY_THIS_DIR);

  /* Set up kind. */
  /* ### not used by loggy; no need to set MODIFY_FLAGS  */
  {
    const char *kindstr
      = svn_hash_gets(atts, ENTRIES_ATTR_KIND);

    entry->kind = svn_node_none;
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
  }

  /* Look for a schedule attribute on this entry. */
  /* ### not used by loggy; no need to set MODIFY_FLAGS  */
  {
    const char *schedulestr
      = svn_hash_gets(atts, ENTRIES_ATTR_SCHEDULE);

    entry->schedule = svn_wc_schedule_normal;
    if (schedulestr)
      {
        if (strcmp(schedulestr, ENTRIES_VALUE_ADD) == 0)
          entry->schedule = svn_wc_schedule_add;
        else if (strcmp(schedulestr, ENTRIES_VALUE_DELETE) == 0)
          entry->schedule = svn_wc_schedule_delete;
        else if (strcmp(schedulestr, ENTRIES_VALUE_REPLACE) == 0)
          entry->schedule = svn_wc_schedule_replace;
        else if (strcmp(schedulestr, "") == 0)
          entry->schedule = svn_wc_schedule_normal;
        else
          return svn_error_createf(
                   SVN_ERR_ENTRY_ATTRIBUTE_INVALID, NULL,
                   _("Entry '%s' has invalid 'schedule' value"),
                   (name ? name : SVN_WC_ENTRY_THIS_DIR));
      }
  }

  /* Is this entry in a state of mental torment (conflict)? */
  entry->prejfile = extract_string_normalize(atts,
                                             ENTRIES_ATTR_PREJFILE,
                                             pool);
  entry->conflict_old = extract_string_normalize(atts,
                                                 ENTRIES_ATTR_CONFLICT_OLD,
                                                 pool);
  entry->conflict_new = extract_string_normalize(atts,
                                                 ENTRIES_ATTR_CONFLICT_NEW,
                                                 pool);
  entry->conflict_wrk = extract_string_normalize(atts,
                                                 ENTRIES_ATTR_CONFLICT_WRK,
                                                 pool);

  /* Is this entry copied? */
  /* ### not used by loggy; no need to set MODIFY_FLAGS  */
  SVN_ERR(do_bool_attr(&entry->copied, atts, ENTRIES_ATTR_COPIED, name));

  /* ### not used by loggy; no need to set MODIFY_FLAGS  */
  entry->copyfrom_url = extract_string(atts, ENTRIES_ATTR_COPYFROM_URL, pool);

  /* ### not used by loggy; no need to set MODIFY_FLAGS  */
  {
    const char *revstr;

    revstr = svn_hash_gets(atts, ENTRIES_ATTR_COPYFROM_REV);
    if (revstr)
      entry->copyfrom_rev = SVN_STR_TO_REV(revstr);
  }

  /* Is this entry deleted?

     ### not used by loggy; no need to set MODIFY_FLAGS  */
  SVN_ERR(do_bool_attr(&entry->deleted, atts, ENTRIES_ATTR_DELETED, name));

  /* Is this entry absent?

     ### not used by loggy; no need to set MODIFY_FLAGS  */
  SVN_ERR(do_bool_attr(&entry->absent, atts, ENTRIES_ATTR_ABSENT, name));

  /* Is this entry incomplete?

     ### not used by loggy; no need to set MODIFY_FLAGS  */
  SVN_ERR(do_bool_attr(&entry->incomplete, atts, ENTRIES_ATTR_INCOMPLETE,
                       name));

  /* Attempt to set up timestamps. */
  /* ### not used by loggy; no need to set MODIFY_FLAGS  */
  {
    const char *text_timestr;

    text_timestr = svn_hash_gets(atts, ENTRIES_ATTR_TEXT_TIME);
    if (text_timestr)
      SVN_ERR(svn_time_from_cstring(&entry->text_time, text_timestr, pool));

    /* Note: we do not persist prop_time, so there is no need to attempt
       to parse a new prop_time value from the log. Certainly, on any
       recent working copy, there will not be a log record to alter
       the prop_time value. */
  }

  /* Checksum. */
  /* ### not used by loggy; no need to set MODIFY_FLAGS  */
  entry->checksum = extract_string(atts, ENTRIES_ATTR_CHECKSUM, pool);

  /* UUID.

     ### not used by loggy; no need to set MODIFY_FLAGS  */
  entry->uuid = extract_string(atts, ENTRIES_ATTR_UUID, pool);

  /* Setup last-committed values. */
  {
    const char *cmt_datestr, *cmt_revstr;

    cmt_datestr = svn_hash_gets(atts, ENTRIES_ATTR_CMT_DATE);
    if (cmt_datestr)
      {
        SVN_ERR(svn_time_from_cstring(&entry->cmt_date, cmt_datestr, pool));
      }
    else
      entry->cmt_date = 0;

    cmt_revstr = svn_hash_gets(atts, ENTRIES_ATTR_CMT_REV);
    if (cmt_revstr)
      {
        entry->cmt_rev = SVN_STR_TO_REV(cmt_revstr);
      }
    else
      entry->cmt_rev = SVN_INVALID_REVNUM;

    entry->cmt_author = extract_string(atts, ENTRIES_ATTR_CMT_AUTHOR, pool);
  }

  /* ### not used by loggy; no need to set MODIFY_FLAGS  */
  entry->lock_token = extract_string(atts, ENTRIES_ATTR_LOCK_TOKEN, pool);
  entry->lock_owner = extract_string(atts, ENTRIES_ATTR_LOCK_OWNER, pool);
  entry->lock_comment = extract_string(atts, ENTRIES_ATTR_LOCK_COMMENT, pool);
  {
    const char *cdate_str =
      svn_hash_gets(atts, ENTRIES_ATTR_LOCK_CREATION_DATE);
    if (cdate_str)
      {
        SVN_ERR(svn_time_from_cstring(&entry->lock_creation_date,
                                      cdate_str, pool));
      }
  }
  /* ----- end of lock handling.  */

  /* Note: if there are attributes for the (deprecated) has_props,
     has_prop_mods, cachable_props, or present_props, then we're just
     going to ignore them. */

  /* Translated size */
  /* ### not used by loggy; no need to set MODIFY_FLAGS  */
  {
    const char *val = svn_hash_gets(atts, ENTRIES_ATTR_WORKING_SIZE);
    if (val)
      {
        /* Cast to off_t; it's safe: we put in an off_t to start with... */
        entry->working_size = (apr_off_t)apr_strtoi64(val, NULL, 0);
      }
  }

  *new_entry = entry;
  return SVN_NO_ERROR;
}