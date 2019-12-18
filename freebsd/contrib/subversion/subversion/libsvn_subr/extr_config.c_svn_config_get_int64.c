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
typedef  int /*<<< orphan*/  svn_config_t ;
typedef  int /*<<< orphan*/  apr_int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_INT64_MAX ; 
 int /*<<< orphan*/  APR_INT64_MIN ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_config_get (int /*<<< orphan*/ *,char const**,char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_cstring_strtoi64 (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

svn_error_t *
svn_config_get_int64(svn_config_t *cfg,
                     apr_int64_t *valuep,
                     const char *section,
                     const char *option,
                     apr_int64_t default_value)
{
  const char *tmp_value;
  svn_config_get(cfg, &tmp_value, section, option, NULL);
  if (tmp_value)
    return svn_cstring_strtoi64(valuep, tmp_value,
                                APR_INT64_MIN, APR_INT64_MAX, 10);

  *valuep = default_value;
  return SVN_NO_ERROR;
}