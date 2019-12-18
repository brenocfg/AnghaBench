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
typedef  int /*<<< orphan*/  svn_fs_x__id_t ;
typedef  int /*<<< orphan*/  svn_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_FS_MALFORMED_NODEREV_ID ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  part_parse (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 

svn_error_t *
svn_fs_x__id_parse(svn_fs_x__id_t *part,
                   const char *data)
{
  if (!part_parse(part, data))
    return svn_error_createf(SVN_ERR_FS_MALFORMED_NODEREV_ID, NULL,
                             "Malformed ID string");

  return SVN_NO_ERROR;
}