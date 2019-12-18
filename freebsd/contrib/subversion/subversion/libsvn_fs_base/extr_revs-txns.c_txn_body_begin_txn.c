#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  fs; } ;
typedef  TYPE_1__ trail_t ;
struct TYPE_8__ {int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;
typedef  TYPE_2__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_fs_id_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct change_txn_prop_args {char const* id; TYPE_2__* value; int /*<<< orphan*/  name; int /*<<< orphan*/  fs; } ;
struct begin_txn_args {int flags; int /*<<< orphan*/  base_rev; int /*<<< orphan*/ * txn_p; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int SVN_FS_TXN_CHECK_LOCKS ; 
 int SVN_FS_TXN_CHECK_OOD ; 
 int SVN_FS_TXN_CLIENT_DATE ; 
 int /*<<< orphan*/  SVN_FS__PROP_TXN_CHECK_LOCKS ; 
 int /*<<< orphan*/  SVN_FS__PROP_TXN_CHECK_OOD ; 
 int /*<<< orphan*/  SVN_FS__PROP_TXN_CLIENT_DATE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_REVISION_DATE ; 
 int /*<<< orphan*/  apr_time_now () ; 
 int /*<<< orphan*/  make_txn (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_base__rev_get_root (int /*<<< orphan*/  const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_bdb__create_txn (char const**,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 void* svn_string_create (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_time_to_cstring (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txn_body_change_txn_prop (struct change_txn_prop_args*,TYPE_1__*) ; 

__attribute__((used)) static svn_error_t *
txn_body_begin_txn(void *baton, trail_t *trail)
{
  struct begin_txn_args *args = baton;
  const svn_fs_id_t *root_id;
  const char *txn_id;

  SVN_ERR(svn_fs_base__rev_get_root(&root_id, trail->fs, args->base_rev,
                                    trail, trail->pool));
  SVN_ERR(svn_fs_bdb__create_txn(&txn_id, trail->fs, root_id,
                                 trail, trail->pool));

  if (args->flags & SVN_FS_TXN_CHECK_OOD)
    {
      struct change_txn_prop_args cpargs;
      cpargs.fs = trail->fs;
      cpargs.id = txn_id;
      cpargs.name = SVN_FS__PROP_TXN_CHECK_OOD;
      cpargs.value = svn_string_create("true", trail->pool);

      SVN_ERR(txn_body_change_txn_prop(&cpargs, trail));
    }

  if (args->flags & SVN_FS_TXN_CHECK_LOCKS)
    {
      struct change_txn_prop_args cpargs;
      cpargs.fs = trail->fs;
      cpargs.id = txn_id;
      cpargs.name = SVN_FS__PROP_TXN_CHECK_LOCKS;
      cpargs.value = svn_string_create("true", trail->pool);

      SVN_ERR(txn_body_change_txn_prop(&cpargs, trail));
    }

  /* Put a datestamp on the newly created txn, so we always know
     exactly how old it is.  (This will help sysadmins identify
     long-abandoned txns that may need to be manually removed.) Do
     this before setting CLIENT_DATE so that it is not recorded as an
     explicit setting. */
  {
    struct change_txn_prop_args cpargs;
    svn_string_t date;
    cpargs.fs = trail->fs;
    cpargs.id = txn_id;
    cpargs.name = SVN_PROP_REVISION_DATE;
    date.data  = svn_time_to_cstring(apr_time_now(), trail->pool);
    date.len = strlen(date.data);
    cpargs.value = &date;
    SVN_ERR(txn_body_change_txn_prop(&cpargs, trail));
  }

  if (args->flags & SVN_FS_TXN_CLIENT_DATE)
    {
      struct change_txn_prop_args cpargs;
      cpargs.fs = trail->fs;
      cpargs.id = txn_id;
      cpargs.name = SVN_FS__PROP_TXN_CLIENT_DATE;
      cpargs.value = svn_string_create("0", trail->pool);

      SVN_ERR(txn_body_change_txn_prop(&cpargs, trail));
    }

  *args->txn_p = make_txn(trail->fs, txn_id, args->base_rev, trail->pool);
  return SVN_NO_ERROR;
}