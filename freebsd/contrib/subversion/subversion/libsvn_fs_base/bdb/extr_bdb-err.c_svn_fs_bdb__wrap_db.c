#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* path; TYPE_3__* fsap_data; } ;
typedef  TYPE_2__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_8__ {TYPE_5__* bdb; } ;
typedef  TYPE_3__ base_fs_data_t ;
struct TYPE_9__ {TYPE_1__* error_info; } ;
struct TYPE_6__ {int /*<<< orphan*/ * pending_errors; } ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char const*) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_fs_bdb__dberrf (TYPE_5__*,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

svn_error_t *
svn_fs_bdb__wrap_db(svn_fs_t *fs, const char *operation, int db_err)
{
  base_fs_data_t *bfd = fs->fsap_data;

  if (! db_err)
    {
      svn_error_clear(bfd->bdb->error_info->pending_errors);
      bfd->bdb->error_info->pending_errors = NULL;
      return SVN_NO_ERROR;
    }

  bfd = fs->fsap_data;
  return svn_fs_bdb__dberrf
    (bfd->bdb, db_err,
     _("Berkeley DB error for filesystem '%s' while %s:\n"),
     fs->path ? fs->path : "(none)", _(operation));
}