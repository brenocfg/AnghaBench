#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  magic; } ;
typedef  TYPE_1__ svn_magic__cookie_t ;
struct TYPE_13__ {scalar_t__ apr_err; } ;
typedef  TYPE_2__ svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_14__ {scalar_t__ size; } ;
typedef  TYPE_3__ apr_finfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_FINFO_SIZE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_ERR_BAD_MIME_TYPE ; 
 TYPE_2__* SVN_NO_ERROR ; 
 char* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 char* magic_file (int /*<<< orphan*/ ,char const*) ; 
 char* strchr (char const*,char) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_2__*) ; 
 TYPE_2__* svn_error_trace (TYPE_2__*) ; 
 int /*<<< orphan*/  svn_io_stat (TYPE_3__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_mime_type_validate (char const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_magic__detect_binary_mimetype(const char **mimetype,
                                  const char *local_abspath,
                                  svn_magic__cookie_t *magic_cookie,
                                  apr_pool_t *result_pool,
                                  apr_pool_t *scratch_pool)
{
  const char *magic_mimetype = NULL;
#ifdef SVN_HAVE_LIBMAGIC
  apr_finfo_t finfo;

  /* Do not ask libmagic for the mime-types of empty files.
   * This prevents mime-types like "application/x-empty" from making
   * Subversion treat empty files as binary. */
  SVN_ERR(svn_io_stat(&finfo, local_abspath, APR_FINFO_SIZE, scratch_pool));
  if (finfo.size > 0)
    {
      magic_mimetype = magic_file(magic_cookie->magic, local_abspath);
      if (magic_mimetype)
        {
          /* Only return binary mime-types. */
          if (strncmp(magic_mimetype, "text/", 5) == 0)
            magic_mimetype = NULL;
          else
            {
              svn_error_t *err;
#ifndef MAGIC_MIME_TYPE
              char *p;

              /* Strip off trailing stuff like " charset=ascii". */
              p = strchr(magic_mimetype, ' ');
              if (p)
                *p = '\0';
#endif
              /* Make sure we got a valid mime type. */
              err = svn_mime_type_validate(magic_mimetype, scratch_pool);
              if (err)
                {
                  if (err->apr_err == SVN_ERR_BAD_MIME_TYPE)
                    {
                      svn_error_clear(err);
                      magic_mimetype = NULL;
                    }
                  else
                    return svn_error_trace(err);
                }
              else
                {
                  /* The string is allocated from memory managed by libmagic
                   * so we must copy it to the result pool. */
                  magic_mimetype = apr_pstrdup(result_pool, magic_mimetype);
                }
            }
        }
    }
#endif

  *mimetype = magic_mimetype;
  return SVN_NO_ERROR;
}