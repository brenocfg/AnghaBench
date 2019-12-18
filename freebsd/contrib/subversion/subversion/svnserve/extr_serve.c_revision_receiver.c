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
typedef  int /*<<< orphan*/  svn_string_t ;
struct TYPE_4__ {int /*<<< orphan*/  has_children; int /*<<< orphan*/  subtractive_merge; int /*<<< orphan*/  revprops; int /*<<< orphan*/  revision; } ;
typedef  TYPE_1__ svn_repos_log_entry_t ;
typedef  int /*<<< orphan*/  svn_ra_svn_conn_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  void* svn_boolean_t ;
struct TYPE_5__ {scalar_t__ stack_depth; void* started; int /*<<< orphan*/ * conn; } ;
typedef  TYPE_2__ log_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 void* TRUE ; 
 int apr_hash_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_compat_log_revprops_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_compat_log_revprops_out_string (int /*<<< orphan*/  const**,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_ra_svn__end_list (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_svn__start_list (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_svn__write_boolean (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_ra_svn__write_data_log_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,void*,unsigned int) ; 
 int /*<<< orphan*/  svn_ra_svn__write_proplist (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
revision_receiver(void *baton,
                  svn_repos_log_entry_t *log_entry,
                  apr_pool_t *scratch_pool)
{
  log_baton_t *b = baton;
  svn_ra_svn_conn_t *conn = b->conn;
  svn_boolean_t invalid_revnum = FALSE;
  const svn_string_t *author, *date, *message;
  unsigned revprop_count;

  if (log_entry->revision == SVN_INVALID_REVNUM)
    {
      /* If the stack depth is zero, we've seen the last revision, so don't
         send it, just return. */
      if (b->stack_depth == 0)
        return SVN_NO_ERROR;

      /* Because the svn protocol won't let us send an invalid revnum, we have
         to fudge here and send an additional flag. */
      log_entry->revision = 0;
      invalid_revnum = TRUE;
      b->stack_depth--;
    }

  svn_compat_log_revprops_out_string(&author, &date, &message,
                                     log_entry->revprops);

  /* Revprops list filtering is somewhat expensive.
     Avoid doing that for the 90% case where only the standard revprops
     have been requested and delivered. */
  if (author && date && message && apr_hash_count(log_entry->revprops) == 3)
    {
      revprop_count = 0;
    }
  else
    {
      svn_compat_log_revprops_clear(log_entry->revprops);
      if (log_entry->revprops)
        revprop_count = apr_hash_count(log_entry->revprops);
      else
        revprop_count = 0;
    }

  /* Open lists once: LOG_ENTRY and LOG_ENTRY->CHANGED_PATHS. */
  if (!b->started)
    {
      SVN_ERR(svn_ra_svn__start_list(conn, scratch_pool));
      SVN_ERR(svn_ra_svn__start_list(conn, scratch_pool));
    }

  /* Close LOG_ENTRY->CHANGED_PATHS. */
  SVN_ERR(svn_ra_svn__end_list(conn, scratch_pool));
  b->started = FALSE;

  /* send LOG_ENTRY main members */
  SVN_ERR(svn_ra_svn__write_data_log_entry(conn, scratch_pool,
                                           log_entry->revision,
                                           author, date, message,
                                           log_entry->has_children,
                                           invalid_revnum, revprop_count));

  /* send LOG_ENTRY->REVPROPS */
  SVN_ERR(svn_ra_svn__start_list(conn, scratch_pool));
  if (revprop_count)
    SVN_ERR(svn_ra_svn__write_proplist(conn, scratch_pool,
                                       log_entry->revprops));
  SVN_ERR(svn_ra_svn__end_list(conn, scratch_pool));

  /* send LOG_ENTRY members that were added in later SVN releases */
  SVN_ERR(svn_ra_svn__write_boolean(conn, scratch_pool,
                                    log_entry->subtractive_merge));
  SVN_ERR(svn_ra_svn__end_list(conn, scratch_pool));

  if (log_entry->has_children)
    b->stack_depth++;

  return SVN_NO_ERROR;
}