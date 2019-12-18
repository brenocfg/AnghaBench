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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_MERGEINFO_PARSE_ERROR ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  apr_pstrndup (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* svn_fspath__canonicalize (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
parse_pathname(const char **input,
               const char *end,
               const char **pathname,
               apr_pool_t *pool)
{
  const char *curr = *input;
  const char *last_colon = NULL;

  /* A pathname may contain colons, so find the last colon before END
     or newline.  We'll consider this the divider between the pathname
     and the revisionlist. */
  while (curr < end && *curr != '\n')
    {
      if (*curr == ':')
        last_colon = curr;
      curr++;
    }

  if (!last_colon)
    return svn_error_create(SVN_ERR_MERGEINFO_PARSE_ERROR, NULL,
                            _("Pathname not terminated by ':'"));

  /* Tolerate relative repository paths, but convert them to absolute.
     ### Efficiency?  1 string duplication here, 2 in canonicalize. */
  *pathname = svn_fspath__canonicalize(apr_pstrndup(pool, *input,
                                                    last_colon - *input),
                                       pool);

  *input = last_colon;

  return SVN_NO_ERROR;
}