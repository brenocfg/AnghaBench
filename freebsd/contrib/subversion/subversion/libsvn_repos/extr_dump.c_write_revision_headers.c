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
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 char const* SVN_REPOS_DUMPFILE_CONTENT_LENGTH ; 
#define  SVN_REPOS_DUMPFILE_REVISION_NUMBER 128 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_key (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_header (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
write_revision_headers(svn_stream_t *stream,
                       apr_hash_t *headers,
                       apr_pool_t *scratch_pool)
{
  const char **h;
  apr_hash_index_t *hi;

  static const char *revision_headers_order[] =
  {
    SVN_REPOS_DUMPFILE_REVISION_NUMBER,  /* must be first */
    NULL
  };

  /* Write some headers in a given order */
  for (h = revision_headers_order; *h; h++)
    {
      SVN_ERR(write_header(stream, headers, *h, scratch_pool));
      svn_hash_sets(headers, *h, NULL);
    }

  /* Write any and all remaining headers except Content-length.
   * ### TODO: use a stable order
   */
  for (hi = apr_hash_first(scratch_pool, headers); hi; hi = apr_hash_next(hi))
    {
      const char *key = apr_hash_this_key(hi);

      if (strcmp(key, SVN_REPOS_DUMPFILE_CONTENT_LENGTH) != 0)
        SVN_ERR(write_header(stream, headers, key, scratch_pool));
    }

  /* Content-length must be last */
  SVN_ERR(write_header(stream, headers, SVN_REPOS_DUMPFILE_CONTENT_LENGTH,
                       scratch_pool));

  return SVN_NO_ERROR;
}