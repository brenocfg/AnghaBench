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
struct TYPE_5__ {scalar_t__ revision; scalar_t__ has_children; scalar_t__ changed_paths2; int /*<<< orphan*/  revprops; } ;
typedef  TYPE_2__ svn_log_entry_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct log_receiver_baton {int message_lines; int merged_message_lines; unsigned int changes; unsigned int merged_changes; int /*<<< orphan*/  merges; scalar_t__ merge_depth; int /*<<< orphan*/  merged_revs; int /*<<< orphan*/  revisions; scalar_t__ quiet; TYPE_1__* ctx; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_4__ {int /*<<< orphan*/  cancel_baton; int /*<<< orphan*/  (* cancel_func ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_IS_VALID_REVNUM (scalar_t__) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 unsigned int apr_hash_count (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_compat_log_revprops_out (char const**,char const**,char const**,int /*<<< orphan*/ ) ; 
 int svn_cstring_count_newlines (char const*) ; 

__attribute__((used)) static svn_error_t *
log_entry_receiver(void *baton,
                   svn_log_entry_t *log_entry,
                   apr_pool_t *pool)
{
  struct log_receiver_baton *lb = baton;
  const char *author;
  const char *date;
  const char *message;

  if (lb->ctx->cancel_func)
    SVN_ERR(lb->ctx->cancel_func(lb->ctx->cancel_baton));

  if (! SVN_IS_VALID_REVNUM(log_entry->revision))
    {
      lb->merge_depth--;
      return SVN_NO_ERROR;
    }

  /* if we don't want counters, we are done */
  if (lb->quiet)
    return SVN_NO_ERROR;

  /* extract the message and do all the other counting */
  svn_compat_log_revprops_out(&author, &date, &message, log_entry->revprops);
  if (log_entry->revision == 0 && message == NULL)
    return SVN_NO_ERROR;

  lb->revisions++;
  if (lb->merge_depth)
    lb->merged_revs++;

  if (message != NULL)
    {
      int count = svn_cstring_count_newlines(message) + 1;
      lb->message_lines += count;
      if (lb->merge_depth)
        lb->merged_message_lines += count;
    }

  if (log_entry->changed_paths2)
    {
      unsigned count = apr_hash_count(log_entry->changed_paths2);
      lb->changes += count;
      if (lb->merge_depth)
        lb->merged_changes += count;
    }

  if (log_entry->has_children)
    {
      lb->merge_depth++;
      lb->merges++;
    }

  return SVN_NO_ERROR;
}