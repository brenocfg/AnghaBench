#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  pool; scalar_t__ config; int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  dbconfig_options ;
typedef  int /*<<< orphan*/  dbconfig_contents ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 int APR_CREATE ; 
 int /*<<< orphan*/  APR_OS_DEFAULT ; 
 int APR_WRITE ; 
 int /*<<< orphan*/  BDB_CONFIG_FILE ; 
 int DB_VERSION_MAJOR ; 
 int DB_VERSION_MINOR ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
#define  SVN_FS_CONFIG_BDB_LOG_AUTOREMOVE 129 
#define  SVN_FS_CONFIG_BDB_TXN_NOSYNC 128 
 scalar_t__ strcmp (void*,char*) ; 
 int strlen (char const*) ; 
 char* svn_dirent_join (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* svn_hash_gets (scalar_t__,char const*) ; 
 int /*<<< orphan*/ * svn_io_file_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_io_file_open (int /*<<< orphan*/ **,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_io_file_write_full (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
bdb_write_config(svn_fs_t *fs)
{
  const char *dbconfig_file_name =
    svn_dirent_join(fs->path, BDB_CONFIG_FILE, fs->pool);
  apr_file_t *dbconfig_file = NULL;
  int i;

  static const char dbconfig_contents[] =
    "# This is the configuration file for the Berkeley DB environment\n"
    "# used by your Subversion repository.\n"
    "# You must run 'svnadmin recover' whenever you modify this file,\n"
    "# for your changes to take effect.\n"
    "\n"
    "### Lock subsystem\n"
    "#\n"
    "# Make sure you read the documentation at:\n"
    "#\n"
    "#   http://docs.oracle.com/cd/E17076_02/html/programmer_reference/lock_max.html\n"
    "#\n"
    "# before tweaking these values.\n"
    "#\n"
    "set_lk_max_locks   2000\n"
    "set_lk_max_lockers 2000\n"
    "set_lk_max_objects 2000\n"
    "\n"
    "### Log file subsystem\n"
    "#\n"
    "# Make sure you read the documentation at:\n"
    "#\n"
    "#   http://docs.oracle.com/cd/E17076_02/html/api_reference/C/envset_lg_bsize.html\n"
    "#   http://docs.oracle.com/cd/E17076_02/html/api_reference/C/envset_lg_max.html\n"
    "#   http://docs.oracle.com/cd/E17076_02/html/programmer_reference/log_limits.html\n"
    "#\n"
    "# Increase the size of the in-memory log buffer from the default\n"
    "# of 32 Kbytes to 256 Kbytes.  Decrease the log file size from\n"
    "# 10 Mbytes to 1 Mbyte.  This will help reduce the amount of disk\n"
    "# space required for hot backups.  The size of the log file must be\n"
    "# at least four times the size of the in-memory log buffer.\n"
    "#\n"
    "# Note: Decreasing the in-memory buffer size below 256 Kbytes will hurt\n"
    "# hurt commit performance. For details, see:\n"
    "#\n"
    "#   http://svn.haxx.se/dev/archive-2002-02/0141.shtml\n"
    "#\n"
    "set_lg_bsize     262144\n"
    "set_lg_max      1048576\n"
    "#\n"
    "# If you see \"log region out of memory\" errors, bump lg_regionmax.\n"
    "# For more information, see:\n"
    "#\n"
    "#   http://docs.oracle.com/cd/E17076_02/html/programmer_reference/log_config.html\n"
    "#   http://svn.haxx.se/users/archive-2004-10/1000.shtml\n"
    "#\n"
    "set_lg_regionmax 131072\n"
    "#\n"
    /* ### Configure this with "svnadmin create --bdb-cache-size" */
    "# The default cache size in BDB is only 256k. As explained in\n"
    "# http://svn.haxx.se/dev/archive-2004-12/0368.shtml, this is too\n"
    "# small for most applications. Bump this number if \"db_stat -m\"\n"
    "# shows too many cache misses.\n"
    "#\n"
    "set_cachesize    0 1048576 1\n";

  /* Run-time configurable options.
     Each option set consists of a minimum required BDB version, a
     config hash key, a header, an inactive form and an active
     form. We always write the header; then, depending on the
     run-time configuration and the BDB version we're compiling
     against, we write either the active or inactive form of the
     value. */
  static const struct
  {
    int bdb_major;
    int bdb_minor;
    const char *config_key;
    const char *header;
    const char *inactive;
    const char *active;
  } dbconfig_options[] = {
    /* Controlled by "svnadmin create --bdb-txn-nosync" */
    { 4, 0, SVN_FS_CONFIG_BDB_TXN_NOSYNC,
      /* header */
      "#\n"
      "# Disable fsync of log files on transaction commit. Read the\n"
      "# documentation about DB_TXN_NOSYNC at:\n"
      "#\n"
      "#   http://docs.oracle.com/cd/E17076_02/html/programmer_reference/log_config.html\n"
      "#\n"
      "# [requires Berkeley DB 4.0]\n"
      "#\n",
      /* inactive */
      "#set_flags DB_TXN_NOSYNC\n",
      /* active */
      "set_flags DB_TXN_NOSYNC\n" },
    /* Controlled by "svnadmin create --bdb-log-keep" */
    { 4, 2, SVN_FS_CONFIG_BDB_LOG_AUTOREMOVE,
      /* header */
      "#\n"
      "# Enable automatic removal of unused transaction log files.\n"
      "# Read the documentation about DB_LOG_AUTOREMOVE at:\n"
      "#\n"
      "#   http://docs.oracle.com/cd/E17076_02/html/programmer_reference/log_config.html\n"
      "#\n"
      "# [requires Berkeley DB 4.2]\n"
      "#\n",
      /* inactive */
      "#set_flags DB_LOG_AUTOREMOVE\n",
      /* active */
      "set_flags DB_LOG_AUTOREMOVE\n" },
  };
  static const int dbconfig_options_length =
    sizeof(dbconfig_options)/sizeof(*dbconfig_options);


  SVN_ERR(svn_io_file_open(&dbconfig_file, dbconfig_file_name,
                           APR_WRITE | APR_CREATE, APR_OS_DEFAULT,
                           fs->pool));

  SVN_ERR(svn_io_file_write_full(dbconfig_file, dbconfig_contents,
                                 sizeof(dbconfig_contents) - 1, NULL,
                                 fs->pool));

  /* Write the variable DB_CONFIG flags. */
  for (i = 0; i < dbconfig_options_length; ++i)
    {
      void *value = NULL;
      const char *choice;

      if (fs->config)
        {
          value = svn_hash_gets(fs->config, dbconfig_options[i].config_key);
        }

      SVN_ERR(svn_io_file_write_full(dbconfig_file,
                                     dbconfig_options[i].header,
                                     strlen(dbconfig_options[i].header),
                                     NULL, fs->pool));

      if (((DB_VERSION_MAJOR == dbconfig_options[i].bdb_major
            && DB_VERSION_MINOR >= dbconfig_options[i].bdb_minor)
           || DB_VERSION_MAJOR > dbconfig_options[i].bdb_major)
          && value != NULL && strcmp(value, "0") != 0)
        choice = dbconfig_options[i].active;
      else
        choice = dbconfig_options[i].inactive;

      SVN_ERR(svn_io_file_write_full(dbconfig_file, choice, strlen(choice),
                                     NULL, fs->pool));
    }

  return svn_io_file_close(dbconfig_file, fs->pool);
}