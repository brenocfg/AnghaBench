#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_4__* fsap_data; } ;
typedef  TYPE_3__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_10__ {TYPE_2__* bdb; } ;
typedef  TYPE_4__ base_fs_data_t ;
struct TYPE_8__ {TYPE_1__* error_info; } ;
struct TYPE_7__ {void (* user_callback ) (char const*,char*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  svn_fs__check_fs (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
base_bdb_set_errcall(svn_fs_t *fs,
                     void (*db_errcall_fcn)(const char *errpfx, char *msg))
{
  base_fs_data_t *bfd = fs->fsap_data;

  SVN_ERR(svn_fs__check_fs(fs, TRUE));
  bfd->bdb->error_info->user_callback = db_errcall_fcn;

  return SVN_NO_ERROR;
}