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
typedef  int /*<<< orphan*/  svn_client_commit_item3_t ;
struct TYPE_3__ {int /*<<< orphan*/  by_path; } ;
typedef  TYPE_1__ svn_client__committables_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ svn_hash_gets (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static svn_client_commit_item3_t *
look_up_committable(svn_client__committables_t *committables,
                    const char *path,
                    apr_pool_t *pool)
{
  return (svn_client_commit_item3_t *)
      svn_hash_gets(committables->by_path, path);
}