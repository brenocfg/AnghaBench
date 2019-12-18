#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_time_t ;
struct TYPE_3__ {void* tm_mon; void* tm_wday; scalar_t__ tm_yday; void* tm_year; scalar_t__ tm_gmtoff; scalar_t__ tm_isdst; void* tm_usec; void* tm_sec; void* tm_min; void* tm_hour; void* tm_mday; } ;
typedef  TYPE_1__ apr_time_exp_t ;
typedef  scalar_t__ apr_status_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  void* apr_int32_t ;

/* Variables and functions */
 scalar_t__ APR_SUCCESS ; 
 int /*<<< orphan*/  OLD_TIMESTAMP_FORMAT ; 
 int /*<<< orphan*/  SVN_ERR_BAD_DATE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  apr_day_snames ; 
 int /*<<< orphan*/  apr_month_snames ; 
 scalar_t__ apr_time_exp_gmt_get (int /*<<< orphan*/ *,TYPE_1__*) ; 
 void* find_matching_string (char*,int,int /*<<< orphan*/ ) ; 
 int sscanf (char const*,int /*<<< orphan*/ ,char*,void**,char*,void**,void**,void**,void**,void**,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 scalar_t__ svn__strtoul (char const*,char const**) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_time_from_cstring(apr_time_t *when, const char *data, apr_pool_t *pool)
{
  apr_time_exp_t exploded_time;
  apr_status_t apr_err;
  char wday[4], month[4];
  const char *c;

  /* Open-code parsing of the new timestamp format, as this
     is a hot path for reading the entries file.  This format looks
     like:  "2001-08-31T04:24:14.966996Z"  */
  exploded_time.tm_year = (apr_int32_t) svn__strtoul(data, &c);
  if (*c++ != '-') goto fail;
  exploded_time.tm_mon = (apr_int32_t) svn__strtoul(c, &c);
  if (*c++ != '-') goto fail;
  exploded_time.tm_mday = (apr_int32_t) svn__strtoul(c, &c);
  if (*c++ != 'T') goto fail;
  exploded_time.tm_hour = (apr_int32_t) svn__strtoul(c, &c);
  if (*c++ != ':') goto fail;
  exploded_time.tm_min = (apr_int32_t) svn__strtoul(c, &c);
  if (*c++ != ':') goto fail;
  exploded_time.tm_sec = (apr_int32_t) svn__strtoul(c, &c);
  if (*c++ != '.') goto fail;
  exploded_time.tm_usec = (apr_int32_t) svn__strtoul(c, &c);
  if (*c++ != 'Z') goto fail;

  exploded_time.tm_year  -= 1900;
  exploded_time.tm_mon   -= 1;
  exploded_time.tm_wday   = 0;
  exploded_time.tm_yday   = 0;
  exploded_time.tm_isdst  = 0;
  exploded_time.tm_gmtoff = 0;

  apr_err = apr_time_exp_gmt_get(when, &exploded_time);
  if (apr_err == APR_SUCCESS)
    return SVN_NO_ERROR;

  return svn_error_create(SVN_ERR_BAD_DATE, NULL, NULL);

 fail:
  /* Try the compatibility option.  This does not need to be fast,
     as this format is no longer generated and the client will convert
     an old-format entries file the first time it reads it.  */
  if (sscanf(data,
             OLD_TIMESTAMP_FORMAT,
             wday,
             &exploded_time.tm_mday,
             month,
             &exploded_time.tm_year,
             &exploded_time.tm_hour,
             &exploded_time.tm_min,
             &exploded_time.tm_sec,
             &exploded_time.tm_usec,
             &exploded_time.tm_yday,
             &exploded_time.tm_isdst,
             &exploded_time.tm_gmtoff) == 11)
    {
      exploded_time.tm_year -= 1900;
      exploded_time.tm_yday -= 1;
      /* Using hard coded limits for the arrays - they are going away
         soon in any case. */
      exploded_time.tm_wday = find_matching_string(wday, 7, apr_day_snames);
      exploded_time.tm_mon = find_matching_string(month, 12, apr_month_snames);

      apr_err = apr_time_exp_gmt_get(when, &exploded_time);
      if (apr_err != APR_SUCCESS)
        return svn_error_create(SVN_ERR_BAD_DATE, NULL, NULL);

      return SVN_NO_ERROR;
    }
  /* Timestamp is something we do not recognize. */
  else
    return svn_error_create(SVN_ERR_BAD_DATE, NULL, NULL);
}