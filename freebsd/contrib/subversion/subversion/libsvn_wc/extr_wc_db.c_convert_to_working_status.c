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
typedef  scalar_t__ svn_wc__db_status_t ;
typedef  int /*<<< orphan*/  svn_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ svn_wc__db_status_added ; 
 scalar_t__ svn_wc__db_status_base_deleted ; 
 scalar_t__ svn_wc__db_status_deleted ; 
 scalar_t__ svn_wc__db_status_excluded ; 
 scalar_t__ svn_wc__db_status_incomplete ; 
 scalar_t__ svn_wc__db_status_normal ; 
 scalar_t__ svn_wc__db_status_not_present ; 

__attribute__((used)) static svn_error_t *
convert_to_working_status(svn_wc__db_status_t *working_status,
                          svn_wc__db_status_t status)
{
  svn_wc__db_status_t work_status = status;

  SVN_ERR_ASSERT(work_status == svn_wc__db_status_normal
                 || work_status == svn_wc__db_status_not_present
                 || work_status == svn_wc__db_status_base_deleted
                 || work_status == svn_wc__db_status_incomplete
                 || work_status == svn_wc__db_status_excluded);

  if (work_status == svn_wc__db_status_excluded)
    {
      *working_status = svn_wc__db_status_excluded;
    }
  else if (work_status == svn_wc__db_status_not_present
           || work_status == svn_wc__db_status_base_deleted)
    {
      /* The caller should scan upwards to detect whether this
         deletion has occurred because this node has been moved
         away, or it is a regular deletion. Also note that the
         deletion could be of the BASE tree, or a child of
         something that has been copied/moved here. */

      *working_status = svn_wc__db_status_deleted;
    }
  else /* normal or incomplete */
    {
      /* The caller should scan upwards to detect whether this
         addition has occurred because of a simple addition,
         a copy, or is the destination of a move. */
      *working_status = svn_wc__db_status_added;
    }

  return SVN_NO_ERROR;
}