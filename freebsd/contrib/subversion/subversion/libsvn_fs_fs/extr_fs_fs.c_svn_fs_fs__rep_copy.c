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
typedef  int /*<<< orphan*/  representation_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * apr_pmemdup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

representation_t *
svn_fs_fs__rep_copy(representation_t *rep,
                    apr_pool_t *pool)
{
  if (rep == NULL)
    return NULL;

  return apr_pmemdup(pool, rep, sizeof(*rep));
}