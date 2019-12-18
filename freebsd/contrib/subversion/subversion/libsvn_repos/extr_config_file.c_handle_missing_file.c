#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_checksum_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct TYPE_3__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_1__ config_access_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ILLEGAL_TARGET ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_checksum (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_checksum_md5 ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char const*) ; 
 scalar_t__ svn_node_file ; 
 scalar_t__ svn_node_none ; 
 int /*<<< orphan*/ * svn_stream_empty (int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
handle_missing_file(svn_stream_t **stream,
                    svn_checksum_t **checksum,
                    config_access_t *access,
                    const char *path,
                    svn_boolean_t must_exist,
                    svn_node_kind_t node_kind)
{
  if (node_kind == svn_node_none && !must_exist)
    {
      *stream = svn_stream_empty(access->pool);
      SVN_ERR(svn_checksum(checksum, svn_checksum_md5, "", 0, access->pool));
    }
  else if (node_kind != svn_node_file)
    {
      return svn_error_createf(SVN_ERR_ILLEGAL_TARGET, NULL,
                               "'%s' is not a file", path);
    }

  return SVN_NO_ERROR;
}