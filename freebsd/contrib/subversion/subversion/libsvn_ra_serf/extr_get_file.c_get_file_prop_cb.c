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
struct TYPE_4__ {char* data; } ;
typedef  TYPE_1__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct file_prop_baton_t {int /*<<< orphan*/  result_pool; int /*<<< orphan*/  props; int /*<<< orphan*/  sha1_checksum; int /*<<< orphan*/  kind; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 char* SVN_DAV_PROP_NS_DAV ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_node_dir ; 
 int /*<<< orphan*/  svn_node_file ; 
 char* svn_ra_serf__svnname_from_wirename (char const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_string_dup (TYPE_1__ const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
get_file_prop_cb(void *baton,
                 const char *path,
                 const char *ns,
                 const char *name,
                 const svn_string_t *value,
                 apr_pool_t *scratch_pool)
{
  struct file_prop_baton_t *fb = baton;
  const char *svn_name;

  if (strcmp(ns, "DAV:") == 0 && strcmp(name, "resourcetype") == 0)
    {
      const char *val = value->data;

      if (strcmp(val, "collection") == 0)
        fb->kind = svn_node_dir;
      else
        fb->kind = svn_node_file;

      return SVN_NO_ERROR;
    }
  else if (strcmp(ns, SVN_DAV_PROP_NS_DAV) == 0
           && strcmp(name, "sha1-checksum") == 0)
    {
      fb->sha1_checksum = apr_pstrdup(fb->result_pool, value->data);
    }

  if (!fb->props)
    return SVN_NO_ERROR;

  svn_name = svn_ra_serf__svnname_from_wirename(ns, name, fb->result_pool);
  if (svn_name)
    {
      svn_hash_sets(fb->props, svn_name,
                    svn_string_dup(value, fb->result_pool));
    }
  return SVN_NO_ERROR;
}