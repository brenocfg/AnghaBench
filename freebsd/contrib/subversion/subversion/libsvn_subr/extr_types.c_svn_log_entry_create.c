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
typedef  int /*<<< orphan*/  svn_log_entry_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * apr_pcalloc (int /*<<< orphan*/ *,int) ; 

svn_log_entry_t *
svn_log_entry_create(apr_pool_t *pool)
{
  svn_log_entry_t *log_entry = apr_pcalloc(pool, sizeof(*log_entry));

  return log_entry;
}