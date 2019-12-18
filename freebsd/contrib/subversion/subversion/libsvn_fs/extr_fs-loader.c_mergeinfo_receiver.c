#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_mergeinfo_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_2__ {int /*<<< orphan*/  result_pool; int /*<<< orphan*/ * mergeinfo; } ;
typedef  TYPE_1__ mergeinfo_receiver_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_mergeinfo_dup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
mergeinfo_receiver(const char *path,
                   svn_mergeinfo_t mergeinfo,
                   void *baton,
                   apr_pool_t *scratch_pool)
{
  mergeinfo_receiver_baton_t *b = baton;
  *b->mergeinfo = svn_mergeinfo_dup(mergeinfo, b->result_pool);

  return SVN_NO_ERROR;
}