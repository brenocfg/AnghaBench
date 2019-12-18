#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_fs_id_t ;
struct TYPE_4__ {int /*<<< orphan*/  number; } ;
struct TYPE_5__ {TYPE_1__ rev_item; } ;
struct TYPE_6__ {TYPE_2__ private_id; } ;
typedef  TYPE_3__ fs_fs__id_t ;
typedef  int /*<<< orphan*/  apr_uint64_t ;

/* Variables and functions */

apr_uint64_t
svn_fs_fs__id_item(const svn_fs_id_t *fs_id)
{
  const fs_fs__id_t *id = (const fs_fs__id_t *)fs_id;

  return id->private_id.rev_item.number;
}