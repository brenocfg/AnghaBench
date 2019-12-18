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
typedef  int /*<<< orphan*/  xlate_handle_t ;
struct TYPE_5__ {char const* frompage; char const* topage; int /*<<< orphan*/ * next; int /*<<< orphan*/  valid; int /*<<< orphan*/ * handle; } ;
typedef  TYPE_1__ xlate_handle_node_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_strerr ;
typedef  scalar_t__ apr_status_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ APR_STATUS_IS_EINVAL (scalar_t__) ; 
 scalar_t__ APR_STATUS_IS_ENOTIMPL (scalar_t__) ; 
 scalar_t__ APR_SUCCESS ; 
 char const* SVN_APR_DEFAULT_CHARSET ; 
 char const* SVN_APR_LOCALE_CHARSET ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/  SVN_ERR_PLUGIN_LOAD_FAILURE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_1__* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  apr_pool_cleanup_null ; 
 int /*<<< orphan*/  apr_pool_cleanup_register (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* apr_psprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,...) ; 
 char const* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ apr_xlate_open (int /*<<< orphan*/ **,char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_create (scalar_t__,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*,char const*) ; 
 int /*<<< orphan*/  svn_strerror (scalar_t__,char*,int) ; 
 scalar_t__ svn_subr__win32_xlate_open (int /*<<< orphan*/ **,char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xlate_handle_node_cleanup ; 

__attribute__((used)) static svn_error_t *
xlate_alloc_handle(xlate_handle_node_t **ret,
                   const char *topage, const char *frompage,
                   apr_pool_t *pool)
{
  apr_status_t apr_err;
  xlate_handle_t *handle;
  const char *name;

  /* The error handling doesn't support the following cases, since we don't
     use them currently.  Catch this here. */
  SVN_ERR_ASSERT(frompage != SVN_APR_DEFAULT_CHARSET
                 && topage != SVN_APR_DEFAULT_CHARSET
                 && (frompage != SVN_APR_LOCALE_CHARSET
                     || topage != SVN_APR_LOCALE_CHARSET));

  /* Try to create a handle. */
#if defined(WIN32)
  apr_err = svn_subr__win32_xlate_open(&handle, topage,
                                       frompage, pool);
  name = "win32-xlate: ";
#else
  apr_err = apr_xlate_open(&handle, topage, frompage, pool);
  name = "APR: ";
#endif

  if (APR_STATUS_IS_EINVAL(apr_err) || APR_STATUS_IS_ENOTIMPL(apr_err))
    handle = NULL;
  else if (apr_err != APR_SUCCESS)
    {
      const char *errstr;
      char apr_strerr[512];

      /* Can't use svn_error_wrap_apr here because it calls functions in
         this file, leading to infinite recursion. */
      if (frompage == SVN_APR_LOCALE_CHARSET)
        errstr = apr_psprintf(pool,
                              _("Can't create a character converter from "
                                "native encoding to '%s'"), topage);
      else if (topage == SVN_APR_LOCALE_CHARSET)
        errstr = apr_psprintf(pool,
                              _("Can't create a character converter from "
                                "'%s' to native encoding"), frompage);
      else
        errstr = apr_psprintf(pool,
                              _("Can't create a character converter from "
                                "'%s' to '%s'"), frompage, topage);

      /* Just put the error on the stack, since svn_error_create duplicates it
         later.  APR_STRERR will be in the local encoding, not in UTF-8, though.
       */
      svn_strerror(apr_err, apr_strerr, sizeof(apr_strerr));
      return svn_error_createf(SVN_ERR_PLUGIN_LOAD_FAILURE,
                               svn_error_create(apr_err, NULL, apr_strerr),
                               "%s%s", name, errstr);
    }

  /* Allocate and initialize the node. */
  *ret = apr_palloc(pool, sizeof(xlate_handle_node_t));
  (*ret)->handle = handle;
  (*ret)->valid = TRUE;
  (*ret)->frompage = ((frompage != SVN_APR_LOCALE_CHARSET)
                      ? apr_pstrdup(pool, frompage) : frompage);
  (*ret)->topage = ((topage != SVN_APR_LOCALE_CHARSET)
                    ? apr_pstrdup(pool, topage) : topage);
  (*ret)->next = NULL;

  /* If we are called from inside a pool cleanup handler, the just created
     xlate handle will be closed when that handler returns by a newly
     registered cleanup handler, however, the handle is still cached by us.
     To prevent this, we register a cleanup handler that will reset the valid
     flag of our node, so we don't use an invalid handle. */
  if (handle)
    apr_pool_cleanup_register(pool, *ret, xlate_handle_node_cleanup,
                              apr_pool_cleanup_null);

  return SVN_NO_ERROR;
}