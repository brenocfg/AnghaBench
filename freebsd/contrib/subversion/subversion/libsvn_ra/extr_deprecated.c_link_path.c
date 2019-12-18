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
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct reporter_3in2_baton {int /*<<< orphan*/  reporter3_baton; TYPE_1__* reporter3; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_2__ {int /*<<< orphan*/ * (* link_path ) (int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_depth_infinity ; 

__attribute__((used)) static svn_error_t *
link_path(void *report_baton,
          const char *path,
          const char *url,
          svn_revnum_t revision,
          svn_boolean_t start_empty,
          const char *lock_token,
          apr_pool_t *pool)
{
  struct reporter_3in2_baton *b = report_baton;
  return b->reporter3->link_path(b->reporter3_baton,
                                 path, url, revision, svn_depth_infinity,
                                 start_empty, lock_token, pool);

}