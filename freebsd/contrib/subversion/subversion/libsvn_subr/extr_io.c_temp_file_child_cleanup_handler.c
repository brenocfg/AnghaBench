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
struct temp_file_cleanup_s {int /*<<< orphan*/  pool; } ;
typedef  int /*<<< orphan*/  apr_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_SUCCESS ; 
 int /*<<< orphan*/  apr_pool_cleanup_kill (int /*<<< orphan*/ ,struct temp_file_cleanup_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  temp_file_plain_cleanup_handler ; 

__attribute__((used)) static apr_status_t
temp_file_child_cleanup_handler(void *baton)
{
  struct  temp_file_cleanup_s *b = baton;

  apr_pool_cleanup_kill(b->pool, b,
                        temp_file_plain_cleanup_handler);

  return APR_SUCCESS;
}