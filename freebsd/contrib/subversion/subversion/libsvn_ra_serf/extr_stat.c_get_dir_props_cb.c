#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char const* data; } ;
typedef  TYPE_1__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct get_dir_baton_t {scalar_t__ is_directory; int /*<<< orphan*/  result_pool; int /*<<< orphan*/  ret_props; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_FS_NOT_DIRECTORY ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 char* svn_ra_serf__svnname_from_wirename (char const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_string_dup (TYPE_1__ const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
get_dir_props_cb(void *baton,
                 const char *path,
                 const char *ns,
                 const char *name,
                 const svn_string_t *value,
                 apr_pool_t *scratch_pool)
{
  struct get_dir_baton_t *db = baton;
  const char *propname;

  propname = svn_ra_serf__svnname_from_wirename(ns, name, db->result_pool);
  if (propname)
    {
      svn_hash_sets(db->ret_props, propname,
                    svn_string_dup(value, db->result_pool));
      return SVN_NO_ERROR;
    }

  if (!db->is_directory)
    {
      if (strcmp(ns, "DAV:") == 0 && strcmp(name, "resourcetype") == 0)
        {
          if (strcmp(value->data, "collection") != 0)
            {
              /* Tell a lie to exit early */
              return svn_error_create(SVN_ERR_FS_NOT_DIRECTORY, NULL,
                                      _("Can't get properties of non-directory"));
            }
          else
            db->is_directory = TRUE;
        }
    }

  return SVN_NO_ERROR;
}