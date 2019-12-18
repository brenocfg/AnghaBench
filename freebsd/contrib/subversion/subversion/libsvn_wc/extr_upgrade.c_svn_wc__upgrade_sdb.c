#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  svn_sqlite__db_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct bump_baton {char const* wcroot_abspath; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/  SVN_ERR_WC_UPGRADE_REQUIRED ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_SQLITE__WITH_LOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
#define  SVN_WC__VERSION 128 
 int SVN_WC__WC_NG_VERSION ; 
 int XXX ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  bump_to_30 ; 
 int /*<<< orphan*/  bump_to_31 ; 
 int /*<<< orphan*/  bump_to_XXX ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  svn_sqlite__read_schema_version (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__with_transaction (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct bump_baton*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_install_schema_statistics (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__version_string_from_format (int) ; 
 int /*<<< orphan*/  wipe_obsolete_files (char const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__upgrade_sdb(int *result_format,
                    const char *wcroot_abspath,
                    svn_sqlite__db_t *sdb,
                    int start_format,
                    apr_pool_t *scratch_pool)
{
  struct bump_baton bb;

  bb.wcroot_abspath = wcroot_abspath;

  if (start_format < SVN_WC__WC_NG_VERSION /* 12 */)
    return svn_error_createf(SVN_ERR_WC_UPGRADE_REQUIRED, NULL,
                             _("Working copy '%s' is too old (format %d, "
                               "created by Subversion %s)"),
                             svn_dirent_local_style(wcroot_abspath,
                                                    scratch_pool),
                             start_format,
                             svn_wc__version_string_from_format(start_format));

  /* Early WCNG formats no longer supported. */
  if (start_format < 19)
    return svn_error_createf(SVN_ERR_WC_UPGRADE_REQUIRED, NULL,
                             _("Working copy '%s' is an old development "
                               "version (format %d); to upgrade it, "
                               "use a format 18 client, then "
                               "use 'tools/dev/wc-ng/bump-to-19.py', then "
                               "use the current client"),
                             svn_dirent_local_style(wcroot_abspath,
                                                    scratch_pool),
                             start_format);
  else if (start_format < 29)
    return svn_error_createf(SVN_ERR_WC_UPGRADE_REQUIRED, NULL,
                             _("Working copy '%s' is an old development "
                               "version (format %d); to upgrade it, "
                               "use a Subversion 1.7-1.9 client, then "
                               "use the current client"),
                             svn_dirent_local_style(wcroot_abspath,
                                                    scratch_pool),
                             start_format);                             

  /* ### need lock-out. only one upgrade at a time. note that other code
     ### cannot use this un-upgraded database until we finish the upgrade.  */

  /* Note: none of these have "break" statements; the fall-through is
     intentional. */
  switch (start_format)
    {
      case 29:
        SVN_ERR(svn_sqlite__with_transaction(sdb, bump_to_30, &bb,
                                             scratch_pool));
        *result_format = 30;

      case 30:
        SVN_ERR(svn_sqlite__with_transaction(sdb, bump_to_31, &bb,
                                             scratch_pool));
        *result_format = 31;
        /* FALLTHROUGH  */
      /* ### future bumps go here.  */
#if 0
      case XXX-1:
        /* Revamp the recording of tree conflicts.  */
        SVN_ERR(svn_sqlite__with_transaction(sdb, bump_to_XXX, &bb,
                                             scratch_pool));
        *result_format = XXX;
        /* FALLTHROUGH  */
#endif
      case SVN_WC__VERSION:
        /* already upgraded */
        *result_format = SVN_WC__VERSION;

        SVN_SQLITE__WITH_LOCK(
            svn_wc__db_install_schema_statistics(sdb, scratch_pool),
            sdb);
    }

#ifdef SVN_DEBUG
  if (*result_format != start_format)
    {
      int schema_version;
      SVN_ERR(svn_sqlite__read_schema_version(&schema_version, sdb, scratch_pool));

      /* If this assertion fails the schema isn't updated correctly */
      SVN_ERR_ASSERT(schema_version == *result_format);
    }
#endif

  /* Zap anything that might be remaining or escaped our notice.  */
  wipe_obsolete_files(wcroot_abspath, scratch_pool);

  return SVN_NO_ERROR;
}