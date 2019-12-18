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
typedef  int /*<<< orphan*/  svn_spillbuf_reader_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int apr_uint64_t ;
typedef  scalar_t__ apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int APR_SIZE_MAX ; 
 int /*<<< orphan*/  APR_UINT64_T_FMT ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/  SVN_ERR_REPOS_BAD_REVISION_REPORT ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 char* apr_palloc (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  apr_psprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_number (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  svn_spillbuf__reader_read (scalar_t__*,int /*<<< orphan*/ *,char*,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
read_string(const char **str, svn_spillbuf_reader_t *reader, apr_pool_t *pool)
{
  apr_uint64_t len;
  apr_size_t size;
  apr_size_t amt;
  char *buf;

  SVN_ERR(read_number(&len, reader, pool));

  /* Len can never be less than zero.  But could len be so large that
     len + 1 wraps around and we end up passing 0 to apr_palloc(),
     thus getting a pointer to no storage?  Probably not (16 exabyte
     string, anyone?) but let's be future-proof anyway. */
  if (len + 1 < len || len + 1 > APR_SIZE_MAX)
    {
      /* xgettext doesn't expand preprocessor definitions, so we must
         pass translatable string to apr_psprintf() function to create
         intermediate string with appropriate format specifier. */
      return svn_error_createf(SVN_ERR_REPOS_BAD_REVISION_REPORT, NULL,
                               apr_psprintf(pool,
                                            _("Invalid length (%%%s) when "
                                              "about to read a string"),
                                            APR_UINT64_T_FMT),
                               len);
    }

  size = (apr_size_t)len;
  buf = apr_palloc(pool, size+1);
  if (size > 0)
    {
      SVN_ERR(svn_spillbuf__reader_read(&amt, reader, buf, size, pool));
      SVN_ERR_ASSERT(amt == size);
    }
  buf[len] = 0;
  *str = buf;
  return SVN_NO_ERROR;
}