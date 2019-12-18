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
struct TYPE_4__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  stream; int /*<<< orphan*/  pool; } ;
typedef  TYPE_1__ logger_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svn_mutex__init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_for_stderr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
logger__create_for_stderr(logger_t **logger,
                          apr_pool_t *pool)
{
  logger_t *result = apr_pcalloc(pool, sizeof(*result));
  result->pool = svn_pool_create(pool);

  SVN_ERR(svn_stream_for_stderr(&result->stream, pool));
  SVN_ERR(svn_mutex__init(&result->mutex, TRUE, pool));

  *logger = result;

  return SVN_NO_ERROR;
}