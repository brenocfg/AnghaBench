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
typedef  int svn_wc__db_status_t ;
typedef  int /*<<< orphan*/  svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_node_none ; 
#define  svn_wc__db_status_excluded 130 
#define  svn_wc__db_status_not_present 129 
#define  svn_wc__db_status_server_excluded 128 

__attribute__((used)) static svn_error_t *
convert_db_kind_to_node_kind(svn_node_kind_t *node_kind,
                             svn_node_kind_t db_kind,
                             svn_wc__db_status_t db_status,
                             svn_boolean_t show_hidden)
{
  *node_kind = db_kind;

  /* Make sure hidden nodes return svn_node_none. */
  if (! show_hidden)
    switch (db_status)
      {
        case svn_wc__db_status_not_present:
        case svn_wc__db_status_server_excluded:
        case svn_wc__db_status_excluded:
          *node_kind = svn_node_none;

        default:
          break;
      }

  return SVN_NO_ERROR;
}