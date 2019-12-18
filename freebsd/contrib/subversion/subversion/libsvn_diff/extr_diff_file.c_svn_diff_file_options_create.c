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
struct TYPE_4__ {int /*<<< orphan*/  context_size; } ;
typedef  TYPE_1__ svn_diff_file_options_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_DIFF__UNIFIED_CONTEXT_SIZE ; 
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 

svn_diff_file_options_t *
svn_diff_file_options_create(apr_pool_t *pool)
{
  svn_diff_file_options_t * opts = apr_pcalloc(pool, sizeof(*opts));

  opts->context_size = SVN_DIFF__UNIFIED_CONTEXT_SIZE;

  return opts;
}