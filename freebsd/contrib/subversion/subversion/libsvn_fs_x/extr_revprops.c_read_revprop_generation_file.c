#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_int64_t ;

/* Variables and functions */
 int GENERATION_READ_RETRY_COUNT ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  apr_sleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_thread_yield () ; 
 int /*<<< orphan*/  svn_cstring_atoi64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ *) ; 
 char* svn_fs_x__path_revprop_generation (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stringbuf_from_file2 (TYPE_1__**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stringbuf_strip_whitespace (TYPE_1__*) ; 

__attribute__((used)) static svn_error_t *
read_revprop_generation_file(apr_int64_t *current,
                             svn_fs_t *fs,
                             apr_pool_t *scratch_pool)
{
  apr_pool_t *iterpool = svn_pool_create(scratch_pool);
  int i;
  svn_error_t *err = SVN_NO_ERROR;
  const char *path = svn_fs_x__path_revprop_generation(fs, scratch_pool);

  /* Retry in case of incomplete file buffer updates. */
  for (i = 0; i < GENERATION_READ_RETRY_COUNT; ++i)
    {
      svn_stringbuf_t *buf;

      svn_error_clear(err);
      svn_pool_clear(iterpool);

      /* Read the generation file. */
      err = svn_stringbuf_from_file2(&buf, path, iterpool);

      /* If we could read the file, it should be complete due to our atomic
       * file replacement scheme. */
      if (!err)
        {
          svn_stringbuf_strip_whitespace(buf);
          SVN_ERR(svn_cstring_atoi64(current, buf->data));
          break;
        }

      /* Got unlucky the file was not available.  Retry. */
#if APR_HAS_THREADS
      apr_thread_yield();
#else
      apr_sleep(0);
#endif
    }

  svn_pool_destroy(iterpool);

  /* If we had to give up, propagate the error. */
  return svn_error_trace(err);
}