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
typedef  int /*<<< orphan*/  svn_wc_adm_access_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ TRUE ; 
 char* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  svn_dirent_split (char const**,char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_check_special_path (char const*,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_node_unknown ; 
 int /*<<< orphan*/ * svn_wc__adm_retrieve_internal2 (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
get_entry_access_info(const char **adm_abspath,
                      const char **entry_name,
                      svn_wc__db_t *db,
                      const char *local_abspath,
                      svn_node_kind_t kind,
                      apr_pool_t *result_pool,
                      apr_pool_t *scratch_pool)
{
  svn_wc_adm_access_t *adm_access;
  svn_boolean_t read_from_subdir = FALSE;

  /* If the caller didn't know the node kind, then stat the path. Maybe
     it is really there, and we can speed up the steps below.  */
  if (kind == svn_node_unknown)
    {
      svn_node_kind_t on_disk;

      /* Do we already have an access baton for LOCAL_ABSPATH?  */
      adm_access = svn_wc__adm_retrieve_internal2(db, local_abspath,
                                                  scratch_pool);
      if (adm_access)
        {
          /* Sweet. The node is a directory.  */
          on_disk = svn_node_dir;
        }
      else
        {
          svn_boolean_t special;

          /* What's on disk?  */
          SVN_ERR(svn_io_check_special_path(local_abspath, &on_disk, &special,
                                            scratch_pool));
        }

      if (on_disk != svn_node_dir)
        {
          /* If this is *anything* besides a directory (FILE, NONE, or
             UNKNOWN), then we cannot treat it as a versioned directory
             containing entries to read. Leave READ_FROM_SUBDIR as FALSE,
             so that the parent will be examined.

             For NONE and UNKNOWN, it may be that metadata exists for the
             node, even though on-disk is unhelpful.

             If NEED_PARENT_STUB is TRUE, and the entry is not a DIRECTORY,
             then we'll error.

             If NEED_PARENT_STUB if FALSE, and we successfully read a stub,
             then this on-disk node is obstructing the read.  */
        }
      else
        {
          /* We found a directory for this UNKNOWN node. Determine whether
             we need to read inside it.  */
          read_from_subdir = TRUE;
        }
    }
  else if (kind == svn_node_dir)
    {
      read_from_subdir = TRUE;
    }

  if (read_from_subdir)
    {
      /* KIND must be a DIR or UNKNOWN (and we found a subdir). We want
         the "real" data, so treat LOCAL_ABSPATH as a versioned directory.  */
      *adm_abspath = apr_pstrdup(result_pool, local_abspath);
      *entry_name = "";
    }
  else
    {
      /* FILE node needs to read the parent directory. Or a DIR node
         needs to read from the parent to get at the stub entry. Or this
         is an UNKNOWN node, and we need to examine the parent.  */
      svn_dirent_split(adm_abspath, entry_name, local_abspath, result_pool);
    }

  return SVN_NO_ERROR;
}