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
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 char* svn_hash_gets (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  svn_stream_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char const*,char const*) ; 

__attribute__((used)) static svn_error_t *
write_header(svn_stream_t *stream,
             apr_hash_t *headers,
             const char *key,
             apr_pool_t *scratch_pool)
{
  const char *val = svn_hash_gets(headers, key);

  if (val)
    {
      SVN_ERR(svn_stream_printf(stream, scratch_pool,
                                "%s: %s\n", key, val));
    }
  return SVN_NO_ERROR;
}