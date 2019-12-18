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
struct TYPE_3__ {scalar_t__ config; } ;
typedef  TYPE_1__ svn_fs_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/ * apr_hash_copy (int /*<<< orphan*/ *,scalar_t__) ; 

apr_hash_t *
svn_fs_config(svn_fs_t *fs, apr_pool_t *pool)
{
  if (fs->config)
    return apr_hash_copy(pool, fs->config);

  return NULL;
}