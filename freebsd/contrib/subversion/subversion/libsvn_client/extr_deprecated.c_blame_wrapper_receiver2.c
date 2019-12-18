#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct blame_receiver_wrapper_baton2 {int /*<<< orphan*/  baton; int /*<<< orphan*/ * (* receiver ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ ,char const*,char const*,char const*,char const*,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_int64_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_REVISION_AUTHOR ; 
 int /*<<< orphan*/  SVN_PROP_REVISION_DATE ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ ,char const*,char const*,char const*,char const*,int /*<<< orphan*/ *) ; 
 char* svn_prop_get_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
blame_wrapper_receiver2(void *baton,
   svn_revnum_t start_revnum,
   svn_revnum_t end_revnum,
   apr_int64_t line_no,
   svn_revnum_t revision,
   apr_hash_t *rev_props,
   svn_revnum_t merged_revision,
   apr_hash_t *merged_rev_props,
   const char *merged_path,
   const char *line,
   svn_boolean_t local_change,
   apr_pool_t *pool)
{
  struct blame_receiver_wrapper_baton2 *brwb = baton;
  const char *author = NULL;
  const char *date = NULL;
  const char *merged_author = NULL;
  const char *merged_date = NULL;

  if (rev_props != NULL)
    {
      author = svn_prop_get_value(rev_props, SVN_PROP_REVISION_AUTHOR);
      date = svn_prop_get_value(rev_props, SVN_PROP_REVISION_DATE);
    }
  if (merged_rev_props != NULL)
    {
      merged_author = svn_prop_get_value(merged_rev_props,
                                         SVN_PROP_REVISION_AUTHOR);
      merged_date = svn_prop_get_value(merged_rev_props,
                                       SVN_PROP_REVISION_DATE);
    }

  if (brwb->receiver)
    return brwb->receiver(brwb->baton, line_no, revision, author, date,
                          merged_revision, merged_author, merged_date,
                          merged_path, line, pool);

  return SVN_NO_ERROR;
}