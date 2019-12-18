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
struct TYPE_4__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  stream; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_1__ logger_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 int APR_APPEND ; 
 int APR_CREATE ; 
 int /*<<< orphan*/  APR_OS_DEFAULT ; 
 int APR_WRITE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svn_io_file_open (int /*<<< orphan*/ **,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_mutex__init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_from_aprfile2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
logger__create(logger_t **logger,
               const char *filename,
               apr_pool_t *pool)
{
  logger_t *result = apr_pcalloc(pool, sizeof(*result));
  apr_file_t *file;

  SVN_ERR(svn_io_file_open(&file, filename,
                           APR_WRITE | APR_CREATE | APR_APPEND,
                           APR_OS_DEFAULT, pool));
  SVN_ERR(svn_mutex__init(&result->mutex, TRUE, pool));

  result->stream = svn_stream_from_aprfile2(file, FALSE,  pool);
  result->pool = svn_pool_create(pool);

  *logger = result;

  return SVN_NO_ERROR;
}