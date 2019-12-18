#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_fs_id_t ;
struct TYPE_5__ {TYPE_2__* fsap_data; } ;
struct TYPE_6__ {TYPE_1__ generic_id; } ;
typedef  TYPE_2__ fs_fs__id_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 TYPE_2__* apr_pmemdup (int /*<<< orphan*/ *,TYPE_2__ const*,int) ; 

svn_fs_id_t *
svn_fs_fs__id_copy(const svn_fs_id_t *source, apr_pool_t *pool)
{
  const fs_fs__id_t *id = (const fs_fs__id_t *)source;
  fs_fs__id_t *new_id = apr_pmemdup(pool, id, sizeof(*new_id));

  new_id->generic_id.fsap_data = new_id;

  return (svn_fs_id_t *)new_id;
}