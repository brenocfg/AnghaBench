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
struct TYPE_4__ {int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_RA_DAV_MALFORMED_DATA ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 char* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 char* apr_strtok (int /*<<< orphan*/ *,char*,char**) ; 
 int /*<<< orphan*/ * svn_cstring_atoi (int*,char const*) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 TYPE_1__* svn_stringbuf_create (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stringbuf_strip_whitespace (TYPE_1__*) ; 

__attribute__((used)) static svn_error_t *
parse_status_line(int *status_code_out,
                  const char **reason,
                  const char *status_line,
                  apr_pool_t *result_pool,
                  apr_pool_t *scratch_pool)
{
  svn_error_t *err;
  const char *token;
  char *tok_status;
  svn_stringbuf_t *temp_buf = svn_stringbuf_create(status_line, scratch_pool);

  svn_stringbuf_strip_whitespace(temp_buf);
  token = apr_strtok(temp_buf->data, " \t\r\n", &tok_status);
  if (token)
    token = apr_strtok(NULL, " \t\r\n", &tok_status);
  if (!token)
    return svn_error_createf(SVN_ERR_RA_DAV_MALFORMED_DATA, NULL,
                             _("Malformed DAV:status '%s'"),
                             status_line);
  err = svn_cstring_atoi(status_code_out, token);
  if (err)
    return svn_error_createf(SVN_ERR_RA_DAV_MALFORMED_DATA, err,
                             _("Malformed DAV:status '%s'"),
                             status_line);

  token = apr_strtok(NULL, " \t\r\n", &tok_status);

  *reason = apr_pstrdup(result_pool, token);

  return SVN_NO_ERROR;
}