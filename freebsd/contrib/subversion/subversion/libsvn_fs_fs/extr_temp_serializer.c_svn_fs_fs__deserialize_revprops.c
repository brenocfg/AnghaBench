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
struct TYPE_3__ {int /*<<< orphan*/  len; void* data; } ;
typedef  TYPE_1__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_HASH_TERMINATOR ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * svn_hash__make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_hash_read2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stream_from_string (TYPE_1__*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_fs__deserialize_revprops(void **out,
                                void *data,
                                apr_size_t data_len,
                                apr_pool_t *pool)
{
  apr_hash_t *properties;
  svn_stream_t *stream;

  svn_string_t buffer;
  buffer.data = data;
  buffer.len = data_len;

  stream = svn_stream_from_string(&buffer, pool);
  properties = svn_hash__make(pool);

  SVN_ERR(svn_hash_read2(properties, stream, SVN_HASH_TERMINATOR, pool));

  /* done */
  *out = properties;

  return SVN_NO_ERROR;
}