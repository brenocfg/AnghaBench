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
struct TYPE_4__ {int verify_format; scalar_t__ timeout; void* exclusive; int /*<<< orphan*/ * state_pool; int /*<<< orphan*/  dir_data; void* enforce_empty_wq; int /*<<< orphan*/ * config; } ;
typedef  TYPE_1__ svn_wc__db_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_config_t ;
typedef  void* svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  scalar_t__ apr_int64_t ;
typedef  scalar_t__ apr_int32_t ;

/* Variables and functions */
 scalar_t__ APR_INT32_MAX ; 
 void* FALSE ; 
 int /*<<< orphan*/  SVN_CONFIG_OPTION_SQLITE_BUSY_TIMEOUT ; 
 int /*<<< orphan*/  SVN_CONFIG_OPTION_SQLITE_EXCLUSIVE ; 
 int /*<<< orphan*/  SVN_CONFIG_SECTION_WORKING_COPY ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  apr_hash_make (int /*<<< orphan*/ *) ; 
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * svn_config_get_bool (int /*<<< orphan*/ *,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/ * svn_config_get_int64 (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__db_open(svn_wc__db_t **db,
                svn_config_t *config,
                svn_boolean_t open_without_upgrade,
                svn_boolean_t enforce_empty_wq,
                apr_pool_t *result_pool,
                apr_pool_t *scratch_pool)
{
  *db = apr_pcalloc(result_pool, sizeof(**db));
  (*db)->config = config;
  (*db)->verify_format = !open_without_upgrade;
  (*db)->enforce_empty_wq = enforce_empty_wq;
  (*db)->dir_data = apr_hash_make(result_pool);

  (*db)->state_pool = result_pool;

  /* Don't need to initialize (*db)->parse_cache, due to the calloc above */
  if (config)
    {
      svn_error_t *err;
      svn_boolean_t sqlite_exclusive = FALSE;
      apr_int64_t timeout;

      err = svn_config_get_bool(config, &sqlite_exclusive,
                                SVN_CONFIG_SECTION_WORKING_COPY,
                                SVN_CONFIG_OPTION_SQLITE_EXCLUSIVE,
                                FALSE);
      if (err)
        {
          svn_error_clear(err);
        }
      else
        (*db)->exclusive = sqlite_exclusive;

      err = svn_config_get_int64(config, &timeout,
                                 SVN_CONFIG_SECTION_WORKING_COPY,
                                 SVN_CONFIG_OPTION_SQLITE_BUSY_TIMEOUT,
                                 0);
      if (err || timeout < 0 || timeout > APR_INT32_MAX)
        svn_error_clear(err);
      else
        (*db)->timeout = (apr_int32_t)timeout;
    }

  return SVN_NO_ERROR;
}