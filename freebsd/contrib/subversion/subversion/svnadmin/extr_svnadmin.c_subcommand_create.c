#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_repos_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct svnadmin_opt_state {char* fs_type; int /*<<< orphan*/  repository_path; TYPE_1__* compatible_version; scalar_t__ bdb_log_keep; scalar_t__ bdb_txn_nosync; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_getopt_t ;
struct TYPE_2__ {char* tag; int /*<<< orphan*/  patch; int /*<<< orphan*/  minor; int /*<<< orphan*/  major; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_CL_ARG_PARSING_ERROR ; 
 int /*<<< orphan*/  SVN_FS_CONFIG_BDB_LOG_AUTOREMOVE ; 
 int /*<<< orphan*/  SVN_FS_CONFIG_BDB_TXN_NOSYNC ; 
 int /*<<< orphan*/  SVN_FS_CONFIG_COMPATIBLE_VERSION ; 
 int /*<<< orphan*/  SVN_FS_CONFIG_FS_TYPE ; 
 int /*<<< orphan*/  SVN_FS_CONFIG_PRE_1_4_COMPATIBLE ; 
 int /*<<< orphan*/  SVN_FS_CONFIG_PRE_1_5_COMPATIBLE ; 
 int /*<<< orphan*/  SVN_FS_CONFIG_PRE_1_6_COMPATIBLE ; 
 int /*<<< orphan*/  SVN_FS_CONFIG_PRE_1_8_COMPATIBLE ; 
 int /*<<< orphan*/  SVN_FS_TYPE_BDB ; 
 int /*<<< orphan*/  SVN_FS_TYPE_FSFS ; 
 int /*<<< orphan*/  SVN_FS_TYPE_FSX ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 char* apr_psprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_args (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_cmdline_fprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_set_warning_func (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  svn_repos_create (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_repos_fs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_version__at_least (TYPE_1__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warning_func ; 

__attribute__((used)) static svn_error_t *
subcommand_create(apr_getopt_t *os, void *baton, apr_pool_t *pool)
{
  struct svnadmin_opt_state *opt_state = baton;
  svn_repos_t *repos;
  apr_hash_t *fs_config = apr_hash_make(pool);

  /* Expect no more arguments. */
  SVN_ERR(parse_args(NULL, os, 0, 0, pool));

  svn_hash_sets(fs_config, SVN_FS_CONFIG_BDB_TXN_NOSYNC,
                (opt_state->bdb_txn_nosync ? "1" :"0"));

  svn_hash_sets(fs_config, SVN_FS_CONFIG_BDB_LOG_AUTOREMOVE,
                (opt_state->bdb_log_keep ? "0" :"1"));

  if (opt_state->fs_type)
    {
      /* With 1.8 we are announcing that BDB is deprecated.  No support
       * has been removed and it will continue to work until some future
       * date.  The purpose here is to discourage people from creating
       * new BDB repositories which they will need to dump/load into
       * FSFS or some new FS type in the future. */
      if (0 == strcmp(opt_state->fs_type, SVN_FS_TYPE_BDB))
        {
          SVN_ERR(svn_cmdline_fprintf(
                      stderr, pool,
                      _("%swarning:"
                        " The \"%s\" repository back-end is deprecated,"
                        " consider using \"%s\" instead.\n"),
                      "svnadmin: ", SVN_FS_TYPE_BDB, SVN_FS_TYPE_FSFS));
          fflush(stderr);
        }
      svn_hash_sets(fs_config, SVN_FS_CONFIG_FS_TYPE, opt_state->fs_type);
    }

  if (opt_state->compatible_version)
    {
      if (! svn_version__at_least(opt_state->compatible_version, 1, 4, 0))
        svn_hash_sets(fs_config, SVN_FS_CONFIG_PRE_1_4_COMPATIBLE, "1");
      if (! svn_version__at_least(opt_state->compatible_version, 1, 5, 0))
        svn_hash_sets(fs_config, SVN_FS_CONFIG_PRE_1_5_COMPATIBLE, "1");
      if (! svn_version__at_least(opt_state->compatible_version, 1, 6, 0))
        svn_hash_sets(fs_config, SVN_FS_CONFIG_PRE_1_6_COMPATIBLE, "1");
      if (! svn_version__at_least(opt_state->compatible_version, 1, 8, 0))
        svn_hash_sets(fs_config, SVN_FS_CONFIG_PRE_1_8_COMPATIBLE, "1");
      /* In 1.9, we figured out that we didn't have to keep extending this
         madness indefinitely. */
      svn_hash_sets(fs_config, SVN_FS_CONFIG_COMPATIBLE_VERSION,
                    apr_psprintf(pool, "%d.%d.%d%s%s",
                                 opt_state->compatible_version->major,
                                 opt_state->compatible_version->minor,
                                 opt_state->compatible_version->patch,
                                 opt_state->compatible_version->tag
                                 ? "-" : "",
                                 opt_state->compatible_version->tag
                                 ? opt_state->compatible_version->tag : ""));
    }

  if (opt_state->compatible_version)
    {
      if (! svn_version__at_least(opt_state->compatible_version, 1, 1, 0)
          /* ### TODO: this NULL check hard-codes knowledge of the library's
                       default fs-type value */
          && (opt_state->fs_type == NULL
              || !strcmp(opt_state->fs_type, SVN_FS_TYPE_FSFS)))
        {
          return svn_error_create(SVN_ERR_CL_ARG_PARSING_ERROR, NULL,
                                  _("Repositories compatible with 1.0.x must "
                                    "use --fs-type=bdb"));
        }

      if (! svn_version__at_least(opt_state->compatible_version, 1, 9, 0)
          && opt_state->fs_type && !strcmp(opt_state->fs_type, SVN_FS_TYPE_FSX))
        {
          return svn_error_createf(SVN_ERR_CL_ARG_PARSING_ERROR, NULL,
                                   _("Repositories compatible with 1.8.x or "
                                     "earlier cannot use --fs-type=%s"),
                                   SVN_FS_TYPE_FSX);
        }
    }

  SVN_ERR(svn_repos_create(&repos, opt_state->repository_path,
                           NULL, NULL, NULL, fs_config, pool));
  svn_fs_set_warning_func(svn_repos_fs(repos), warning_func, NULL);
  return SVN_NO_ERROR;
}