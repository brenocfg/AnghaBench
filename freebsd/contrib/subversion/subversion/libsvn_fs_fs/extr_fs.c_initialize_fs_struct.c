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
struct TYPE_5__ {TYPE_2__* fsap_data; int /*<<< orphan*/ * vtable; int /*<<< orphan*/  pool; } ;
typedef  TYPE_1__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_6__ {int /*<<< orphan*/  flush_to_disk; scalar_t__ revprop_prefix; int /*<<< orphan*/  use_log_addressing; } ;
typedef  TYPE_2__ fs_fs_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_2__* apr_pcalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fs_vtable ; 

__attribute__((used)) static svn_error_t *
initialize_fs_struct(svn_fs_t *fs)
{
  fs_fs_data_t *ffd = apr_pcalloc(fs->pool, sizeof(*ffd));
  ffd->use_log_addressing = FALSE;
  ffd->revprop_prefix = 0;
  ffd->flush_to_disk = TRUE;

  fs->vtable = &fs_vtable;
  fs->fsap_data = ffd;
  return SVN_NO_ERROR;
}