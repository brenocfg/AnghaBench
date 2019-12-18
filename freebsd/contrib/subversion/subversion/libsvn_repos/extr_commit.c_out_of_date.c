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
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_FS_TXN_OUT_OF_DATE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_node_file ; 

__attribute__((used)) static svn_error_t *
out_of_date(const char *path, svn_node_kind_t kind)
{
  return svn_error_createf(SVN_ERR_FS_TXN_OUT_OF_DATE, NULL,
                           (kind == svn_node_dir
                            ? _("Directory '%s' is out of date")
                            : kind == svn_node_file
                            ? _("File '%s' is out of date")
                            : _("'%s' is out of date")),
                           path);
}