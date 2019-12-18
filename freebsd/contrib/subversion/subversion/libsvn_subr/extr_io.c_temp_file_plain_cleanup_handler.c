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
struct temp_file_cleanup_s {int /*<<< orphan*/  pool; scalar_t__ fname_apr; } ;
typedef  int /*<<< orphan*/  apr_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_SUCCESS ; 
 int /*<<< orphan*/  WIN32_RETRY_LOOP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_file_remove (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static apr_status_t
temp_file_plain_cleanup_handler(void *baton)
{
  struct  temp_file_cleanup_s *b = baton;
  apr_status_t apr_err = APR_SUCCESS;

  if (b->fname_apr)
    {
      apr_err = apr_file_remove(b->fname_apr, b->pool);
      WIN32_RETRY_LOOP(apr_err, apr_file_remove(b->fname_apr, b->pool));
    }

  return apr_err;
}