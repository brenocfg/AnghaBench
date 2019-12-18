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
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_4__ {char* path; } ;
typedef  TYPE_1__ apr_uri_t ;
typedef  scalar_t__ apr_status_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_RA_ILLEGAL_URL ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 char* apr_pstrdup (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ apr_uri_parse (int /*<<< orphan*/ *,char const*,TYPE_1__*) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 

svn_error_t *
svn_ra_serf__uri_parse(apr_uri_t *uri,
                       const char *url_str,
                       apr_pool_t *result_pool)
{
  apr_status_t status;

  status = apr_uri_parse(result_pool, url_str, uri);
  if (status)
    {
      /* Do not use returned error status in error message because currently
         apr_uri_parse() returns APR_EGENERAL for all parsing errors. */
      return svn_error_createf(SVN_ERR_RA_ILLEGAL_URL, NULL,
                               _("Illegal URL '%s'"),
                               url_str);
    }

  /* Depending the version of apr-util in use, for root paths uri.path
     will be NULL or "", where serf requires "/". */
  if (uri->path == NULL || uri->path[0] == '\0')
    {
      uri->path = apr_pstrdup(result_pool, "/");
    }

  return SVN_NO_ERROR;
}