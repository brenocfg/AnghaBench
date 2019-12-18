#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  path; TYPE_3__* fsap_data; } ;
typedef  TYPE_1__ svn_fs_t ;
struct TYPE_12__ {int /*<<< orphan*/  apr_err; } ;
typedef  TYPE_2__ svn_error_t ;
typedef  int /*<<< orphan*/  bdb_env_baton_t ;
struct TYPE_13__ {int /*<<< orphan*/ * bdb; int /*<<< orphan*/  miscellaneous; int /*<<< orphan*/  checksum_reps; int /*<<< orphan*/  node_origins; int /*<<< orphan*/  lock_tokens; int /*<<< orphan*/  locks; int /*<<< orphan*/  uuids; int /*<<< orphan*/  strings; int /*<<< orphan*/  representations; int /*<<< orphan*/  changes; int /*<<< orphan*/  copies; int /*<<< orphan*/  transactions; int /*<<< orphan*/  revisions; int /*<<< orphan*/  nodes; } ;
typedef  TYPE_3__ base_fs_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 TYPE_2__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  cleanup_fs_db (TYPE_1__*,int /*<<< orphan*/ *,char*) ; 
 TYPE_2__* svn_error_createf (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* svn_fs_bdb__close (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
cleanup_fs(svn_fs_t *fs)
{
  base_fs_data_t *bfd = fs->fsap_data;
  bdb_env_baton_t *bdb = (bfd ? bfd->bdb : NULL);

  if (!bdb)
    return SVN_NO_ERROR;

  /* Close the databases.  */
  SVN_ERR(cleanup_fs_db(fs, &bfd->nodes, "nodes"));
  SVN_ERR(cleanup_fs_db(fs, &bfd->revisions, "revisions"));
  SVN_ERR(cleanup_fs_db(fs, &bfd->transactions, "transactions"));
  SVN_ERR(cleanup_fs_db(fs, &bfd->copies, "copies"));
  SVN_ERR(cleanup_fs_db(fs, &bfd->changes, "changes"));
  SVN_ERR(cleanup_fs_db(fs, &bfd->representations, "representations"));
  SVN_ERR(cleanup_fs_db(fs, &bfd->strings, "strings"));
  SVN_ERR(cleanup_fs_db(fs, &bfd->uuids, "uuids"));
  SVN_ERR(cleanup_fs_db(fs, &bfd->locks, "locks"));
  SVN_ERR(cleanup_fs_db(fs, &bfd->lock_tokens, "lock-tokens"));
  SVN_ERR(cleanup_fs_db(fs, &bfd->node_origins, "node-origins"));
  SVN_ERR(cleanup_fs_db(fs, &bfd->checksum_reps, "checksum-reps"));
  SVN_ERR(cleanup_fs_db(fs, &bfd->miscellaneous, "miscellaneous"));

  /* Finally, close the environment.  */
  bfd->bdb = 0;
  {
    svn_error_t *err = svn_fs_bdb__close(bdb);
    if (err)
      return svn_error_createf
        (err->apr_err, err,
         _("Berkeley DB error for filesystem '%s'"
           " while closing environment:\n"),
         fs->path);
  }
  return SVN_NO_ERROR;
}