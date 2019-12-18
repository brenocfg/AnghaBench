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
struct blame_receiver_wrapper_baton {int /*<<< orphan*/  baton; int /*<<< orphan*/ * (* receiver ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,char const*,char const*,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_int64_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,char const*,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
blame_wrapper_receiver(void *baton,
                       apr_int64_t line_no,
                       svn_revnum_t revision,
                       const char *author,
                       const char *date,
                       svn_revnum_t merged_revision,
                       const char *merged_author,
                       const char *merged_date,
                       const char *merged_path,
                       const char *line,
                       apr_pool_t *pool)
{
  struct blame_receiver_wrapper_baton *brwb = baton;

  if (brwb->receiver)
    return brwb->receiver(brwb->baton,
                          line_no, revision, author, date, line, pool);

  return SVN_NO_ERROR;
}