#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  path; TYPE_3__* fsap_data; int /*<<< orphan*/ * vtable; } ;
typedef  TYPE_1__ svn_fs_t ;
struct TYPE_17__ {int /*<<< orphan*/  apr_err; } ;
typedef  TYPE_2__ svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct TYPE_18__ {TYPE_5__* bdb; int /*<<< orphan*/  checksum_reps; int /*<<< orphan*/  miscellaneous; int /*<<< orphan*/  node_origins; int /*<<< orphan*/  lock_tokens; int /*<<< orphan*/  locks; int /*<<< orphan*/  uuids; int /*<<< orphan*/  strings; int /*<<< orphan*/  representations; int /*<<< orphan*/  changes; int /*<<< orphan*/  copies; int /*<<< orphan*/  transactions; int /*<<< orphan*/  revisions; int /*<<< orphan*/  nodes; } ;
typedef  TYPE_3__ base_fs_data_t ;
struct TYPE_19__ {int /*<<< orphan*/  env; } ;

/* Variables and functions */
 int /*<<< orphan*/  BDB_WRAP (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  N_ (char*) ; 
 int /*<<< orphan*/  SVN_BDB_STANDARD_ENV_FLAGS ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int SVN_FS_BASE__MIN_MISCELLANY_FORMAT ; 
 int SVN_FS_BASE__MIN_NODE_ORIGINS_FORMAT ; 
 int SVN_FS_BASE__MIN_REP_SHARING_FORMAT ; 
 TYPE_2__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_3__* apr_pcalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  apr_pool_cleanup_null ; 
 int /*<<< orphan*/  apr_pool_cleanup_register (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  bdb_write_config (TYPE_1__*) ; 
 int /*<<< orphan*/  cleanup_fs_apr ; 
 int /*<<< orphan*/  fs_vtable ; 
 TYPE_2__* svn_error_createf (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs__check_fs (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* svn_fs_bdb__open (TYPE_5__**,char const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_bdb__open_changes_table (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_bdb__open_checksum_reps_table (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_bdb__open_copies_table (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_bdb__open_lock_tokens_table (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_bdb__open_locks_table (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_bdb__open_miscellaneous_table (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_bdb__open_node_origins_table (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_bdb__open_nodes_table (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_bdb__open_reps_table (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_bdb__open_revisions_table (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_bdb__open_strings_table (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_bdb__open_transactions_table (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_bdb__open_uuids_table (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
open_databases(svn_fs_t *fs,
               svn_boolean_t create,
               int format,
               const char *path)
{
  base_fs_data_t *bfd;

  SVN_ERR(svn_fs__check_fs(fs, FALSE));

  bfd = apr_pcalloc(fs->pool, sizeof(*bfd));
  fs->vtable = &fs_vtable;
  fs->fsap_data = bfd;

  /* Initialize the fs's path. */
  fs->path = apr_pstrdup(fs->pool, path);

  if (create)
    SVN_ERR(bdb_write_config(fs));

  /* Create the Berkeley DB environment.  */
  {
    svn_error_t *err = svn_fs_bdb__open(&(bfd->bdb), path,
                                        SVN_BDB_STANDARD_ENV_FLAGS,
                                        0666, fs->pool);
    if (err)
      {
        if (create)
          return svn_error_createf
            (err->apr_err, err,
             _("Berkeley DB error for filesystem '%s'"
               " while creating environment:\n"),
             fs->path);
        else
          return svn_error_createf
            (err->apr_err, err,
             _("Berkeley DB error for filesystem '%s'"
               " while opening environment:\n"),
             fs->path);
      }
  }

  /* We must register the FS cleanup function *after* opening the
     environment, so that it's run before the environment baton
     cleanup. */
  apr_pool_cleanup_register(fs->pool, fs, cleanup_fs_apr,
                            apr_pool_cleanup_null);


  /* Create the databases in the environment.  */
  SVN_ERR(BDB_WRAP(fs, (create
                        ? N_("creating 'nodes' table")
                        : N_("opening 'nodes' table")),
                   svn_fs_bdb__open_nodes_table(&bfd->nodes,
                                                bfd->bdb->env,
                                                create)));
  SVN_ERR(BDB_WRAP(fs, (create
                        ? N_("creating 'revisions' table")
                        : N_("opening 'revisions' table")),
                   svn_fs_bdb__open_revisions_table(&bfd->revisions,
                                                    bfd->bdb->env,
                                                    create)));
  SVN_ERR(BDB_WRAP(fs, (create
                        ? N_("creating 'transactions' table")
                        : N_("opening 'transactions' table")),
                   svn_fs_bdb__open_transactions_table(&bfd->transactions,
                                                       bfd->bdb->env,
                                                       create)));
  SVN_ERR(BDB_WRAP(fs, (create
                        ? N_("creating 'copies' table")
                        : N_("opening 'copies' table")),
                   svn_fs_bdb__open_copies_table(&bfd->copies,
                                                 bfd->bdb->env,
                                                 create)));
  SVN_ERR(BDB_WRAP(fs, (create
                        ? N_("creating 'changes' table")
                        : N_("opening 'changes' table")),
                   svn_fs_bdb__open_changes_table(&bfd->changes,
                                                  bfd->bdb->env,
                                                  create)));
  SVN_ERR(BDB_WRAP(fs, (create
                        ? N_("creating 'representations' table")
                        : N_("opening 'representations' table")),
                   svn_fs_bdb__open_reps_table(&bfd->representations,
                                               bfd->bdb->env,
                                               create)));
  SVN_ERR(BDB_WRAP(fs, (create
                        ? N_("creating 'strings' table")
                        : N_("opening 'strings' table")),
                   svn_fs_bdb__open_strings_table(&bfd->strings,
                                                  bfd->bdb->env,
                                                  create)));
  SVN_ERR(BDB_WRAP(fs, (create
                        ? N_("creating 'uuids' table")
                        : N_("opening 'uuids' table")),
                   svn_fs_bdb__open_uuids_table(&bfd->uuids,
                                                bfd->bdb->env,
                                                create)));
  SVN_ERR(BDB_WRAP(fs, (create
                        ? N_("creating 'locks' table")
                        : N_("opening 'locks' table")),
                   svn_fs_bdb__open_locks_table(&bfd->locks,
                                                bfd->bdb->env,
                                                create)));
  SVN_ERR(BDB_WRAP(fs, (create
                        ? N_("creating 'lock-tokens' table")
                        : N_("opening 'lock-tokens' table")),
                   svn_fs_bdb__open_lock_tokens_table(&bfd->lock_tokens,
                                                      bfd->bdb->env,
                                                      create)));

  if (format >= SVN_FS_BASE__MIN_NODE_ORIGINS_FORMAT)
    {
      SVN_ERR(BDB_WRAP(fs, (create
                            ? N_("creating 'node-origins' table")
                            : N_("opening 'node-origins' table")),
                       svn_fs_bdb__open_node_origins_table(&bfd->node_origins,
                                                           bfd->bdb->env,
                                                           create)));
    }

  if (format >= SVN_FS_BASE__MIN_MISCELLANY_FORMAT)
    {
      SVN_ERR(BDB_WRAP(fs, (create
                            ? N_("creating 'miscellaneous' table")
                            : N_("opening 'miscellaneous' table")),
                       svn_fs_bdb__open_miscellaneous_table(&bfd->miscellaneous,
                                                            bfd->bdb->env,
                                                            create)));
    }

  if (format >= SVN_FS_BASE__MIN_REP_SHARING_FORMAT)
    {
      SVN_ERR(BDB_WRAP(fs, (create
                            ? N_("creating 'checksum-reps' table")
                            : N_("opening 'checksum-reps' table")),
                       svn_fs_bdb__open_checksum_reps_table(&bfd->checksum_reps,
                                                            bfd->bdb->env,
                                                            create)));
    }

  return SVN_NO_ERROR;
}