#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* fsap_data; } ;
typedef  TYPE_1__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct TYPE_5__ {int /*<<< orphan*/  use_log_addressing; } ;
typedef  TYPE_2__ fs_fs_data_t ;

/* Variables and functions */

svn_boolean_t
svn_fs_fs__use_log_addressing(svn_fs_t *fs)
{
  fs_fs_data_t *ffd = fs->fsap_data;
  return ffd->use_log_addressing;
}