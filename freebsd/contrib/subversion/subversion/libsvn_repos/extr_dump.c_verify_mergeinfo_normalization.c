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
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_2__ {int /*<<< orphan*/  pool; } ;
struct verify_mergeinfo_normalization_baton {int /*<<< orphan*/  path; int /*<<< orphan*/  notify_baton; int /*<<< orphan*/  notify_func; TYPE_1__ buffer; int /*<<< orphan*/  normalized_paths; } ;
typedef  int /*<<< orphan*/  apr_ssize_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_MERGEINFO ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ ,char const*) ; 
 char const* normalized_collision ; 
 char const* normalized_unique ; 
 int /*<<< orphan*/  notify_warning (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* svn_hash_gets (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_repos_notify_warning_mergeinfo_collision ; 
 int /*<<< orphan*/  svn_utf__normalize (char const**,char const* const,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static svn_error_t *
verify_mergeinfo_normalization(void *baton, const void *key, apr_ssize_t klen,
                               void *val, apr_pool_t *iterpool)
{
  struct verify_mergeinfo_normalization_baton *const vb = baton;

  const char *const path = key;
  const char *normpath;
  const char *found;

  SVN_ERR(svn_utf__normalize(&normpath, path, klen, &vb->buffer));
  found = svn_hash_gets(vb->normalized_paths, normpath);
  if (!found)
      svn_hash_sets(vb->normalized_paths,
                    apr_pstrdup(vb->buffer.pool, normpath),
                    normalized_unique);
  else if (found == normalized_collision)
    /* Skip already reported collision */;
  else
    {
      /* Report path collision in mergeinfo */
      svn_hash_sets(vb->normalized_paths,
                    apr_pstrdup(vb->buffer.pool, normpath),
                    normalized_collision);

      notify_warning(iterpool, vb->notify_func, vb->notify_baton,
                     svn_repos_notify_warning_mergeinfo_collision,
                     _("Duplicate representation of path '%s'"
                       " in %s property of '%s'"),
                     normpath, SVN_PROP_MERGEINFO, vb->path);
    }
  return SVN_NO_ERROR;
}