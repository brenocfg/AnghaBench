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
typedef  scalar_t__ apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_EINVAL ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 char* apr_pstrndup (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  svn_ctype_isascii (char const) ; 
 scalar_t__ svn_ctype_iscntrl (char const) ; 
 int /*<<< orphan*/  svn_ctype_isspace (char const) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static svn_error_t *
check_non_ascii(const char *data, apr_size_t len, apr_pool_t *pool)
{
  const char *data_start = data;

  for (; len > 0; --len, data++)
    {
      if ((! svn_ctype_isascii(*data))
          || ((! svn_ctype_isspace(*data))
              && svn_ctype_iscntrl(*data)))
        {
          /* Show the printable part of the data, followed by the
             decimal code of the questionable character.  Because if a
             user ever gets this error, she's going to have to spend
             time tracking down the non-ASCII data, so we want to help
             as much as possible.  And yes, we just call the unsafe
             data "non-ASCII", even though the actual constraint is
             somewhat more complex than that. */

          if (data - data_start)
            {
              const char *error_data
                = apr_pstrndup(pool, data_start, (data - data_start));

              return svn_error_createf
                (APR_EINVAL, NULL,
                 _("Safe data '%s' was followed by non-ASCII byte %d: "
                   "unable to convert to/from UTF-8"),
                 error_data, *((const unsigned char *) data));
            }
          else
            {
              return svn_error_createf
                (APR_EINVAL, NULL,
                 _("Non-ASCII character (code %d) detected, "
                   "and unable to convert to/from UTF-8"),
                 *((const unsigned char *) data));
            }
        }
    }

  return SVN_NO_ERROR;
}