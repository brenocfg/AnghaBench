#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  len; scalar_t__ data; } ;
typedef  TYPE_2__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_ra_serf__xml_estate_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_7__ {int /*<<< orphan*/  pool; TYPE_1__* lock; } ;
typedef  TYPE_3__ lock_info_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
struct TYPE_5__ {char* token; void* comment; scalar_t__ expiration_date; } ;

/* Variables and functions */
 int HREF ; 
 int OWNER ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_RA_DAV_MALFORMED_DATA ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int TIMEOUT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  apr_collapse_spaces (char*,char*) ; 
 void* apr_pstrmemdup (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ apr_time_from_sec (unsigned int) ; 
 scalar_t__ apr_time_now () ; 
 scalar_t__ strcasecmp (scalar_t__,char*) ; 
 scalar_t__ strncasecmp (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  svn_cstring_atoui (unsigned int*,scalar_t__) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static svn_error_t *
locks_closed(svn_ra_serf__xml_estate_t *xes,
             void *baton,
             int leaving_state,
             const svn_string_t *cdata,
             apr_hash_t *attrs,
             apr_pool_t *scratch_pool)
{
  lock_info_t *lock_ctx = baton;

  if (leaving_state == TIMEOUT)
    {
      if (strcasecmp(cdata->data, "Infinite") == 0)
        lock_ctx->lock->expiration_date = 0;
      else if (strncasecmp(cdata->data, "Second-", 7) == 0)
        {
          unsigned n;
          SVN_ERR(svn_cstring_atoui(&n, cdata->data+7));

          lock_ctx->lock->expiration_date = apr_time_now() +
                                            apr_time_from_sec(n);
        }
      else
         return svn_error_createf(SVN_ERR_RA_DAV_MALFORMED_DATA, NULL,
                                  _("Invalid LOCK timeout value '%s'"),
                                  cdata->data);
    }
  else if (leaving_state == HREF)
    {
      if (cdata->len)
        {
          char *buf = apr_pstrmemdup(lock_ctx->pool, cdata->data, cdata->len);

          apr_collapse_spaces(buf, buf);
          lock_ctx->lock->token = buf;
        }
    }
  else if (leaving_state == OWNER)
    {
      if (cdata->len)
        {
          lock_ctx->lock->comment = apr_pstrmemdup(lock_ctx->pool,
                                                   cdata->data, cdata->len);
        }
    }

  return SVN_NO_ERROR;
}