#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int len; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_checksum_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_OS_DEFAULT ; 
 int APR_PATH_MAX ; 
 int /*<<< orphan*/  APR_READ ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 char* apr_psprintf (int /*<<< orphan*/ *,char*,unsigned int) ; 
 char* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  svn_checksum (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_checksum_sha1 ; 
 char* svn_checksum_to_cstring (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_close (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_del_on_pool_cleanup ; 
 int /*<<< orphan*/  svn_io_file_open (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_readline (int /*<<< orphan*/ *,TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_write_full (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_open_unique_file3 (int /*<<< orphan*/ **,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stringbuf_insert (TYPE_1__*,int /*<<< orphan*/ ,char const*,scalar_t__) ; 
 int /*<<< orphan*/  svn_stringbuf_remove (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static svn_error_t *
transform_link_to_git(const char **new_tmpfile,
                      const char **git_sha1,
                      const char *orig_tmpfile,
                      apr_pool_t *result_pool,
                      apr_pool_t *scratch_pool)
{
  apr_file_t *orig;
  apr_file_t *gitlike;
  svn_stringbuf_t *line;

  *git_sha1 = NULL;

  SVN_ERR(svn_io_file_open(&orig, orig_tmpfile, APR_READ, APR_OS_DEFAULT,
                           scratch_pool));
  SVN_ERR(svn_io_open_unique_file3(&gitlike, new_tmpfile, NULL,
                                   svn_io_file_del_on_pool_cleanup,
                                   result_pool, scratch_pool));

  SVN_ERR(svn_io_file_readline(orig, &line, NULL, NULL, 2 * APR_PATH_MAX + 2,
                               scratch_pool, scratch_pool));

  if (line->len > 5 && !strncmp(line->data, "link ", 5))
    {
      const char *sz_str;
      svn_checksum_t *checksum;

      svn_stringbuf_remove(line, 0, 5);

      SVN_ERR(svn_io_file_write_full(gitlike, line->data, line->len,
                                     NULL, scratch_pool));

      /* git calculates the sha over "blob X\0" + the actual data,
         where X is the decimal size of the blob. */
      sz_str = apr_psprintf(scratch_pool, "blob %u", (unsigned int)line->len);
      svn_stringbuf_insert(line, 0, sz_str, strlen(sz_str) + 1);

      SVN_ERR(svn_checksum(&checksum, svn_checksum_sha1,
                           line->data, line->len, scratch_pool));

      *git_sha1 = svn_checksum_to_cstring(checksum, result_pool);
    }
  else
    {
      /* Not a link... so can't convert */
      *new_tmpfile = apr_pstrdup(result_pool, orig_tmpfile);
    }

  SVN_ERR(svn_io_file_close(orig, scratch_pool));
  SVN_ERR(svn_io_file_close(gitlike, scratch_pool));
  return SVN_NO_ERROR;
}