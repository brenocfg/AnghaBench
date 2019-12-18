#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_checksum_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct TYPE_8__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_2__ config_access_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  handle_missing_file (int /*<<< orphan*/ **,int /*<<< orphan*/ **,TYPE_2__*,char const*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  svn_checksum (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_checksum_md5 ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_io_check_path (char const*,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_file ; 
 int /*<<< orphan*/ * svn_stream_from_stringbuf (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stringbuf_from_file2 (TYPE_1__**,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
get_file_config(svn_stream_t **stream,
                svn_checksum_t **checksum,
                config_access_t *access,
                const char *path,
                svn_boolean_t must_exist,
                apr_pool_t *scratch_pool)
{
  svn_stringbuf_t *contents;
  svn_node_kind_t node_kind;

  /* Special case: non-existent paths may be handled as "empty" contents. */
  SVN_ERR(svn_io_check_path(path, &node_kind, scratch_pool));
  if (node_kind != svn_node_file)
    return svn_error_trace(handle_missing_file(stream, checksum, access,
                                               path, must_exist, node_kind));

  /* Now, we should be able to read the file. */
  SVN_ERR(svn_stringbuf_from_file2(&contents, path, access->pool));

  /* calculate MD5 over the whole file contents */
  SVN_ERR(svn_checksum(checksum, svn_checksum_md5,
                       contents->data, contents->len, access->pool));
  *stream = svn_stream_from_stringbuf(contents, access->pool);

  return SVN_NO_ERROR;
}