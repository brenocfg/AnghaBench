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
struct edit_baton {int /*<<< orphan*/  notify_baton; int /*<<< orphan*/  notify_func; } ;
struct dir_baton {int /*<<< orphan*/  path; struct edit_baton* edit_baton; } ;
struct TYPE_2__ {int /*<<< orphan*/  pool; } ;
struct check_name_collision_baton {TYPE_1__ buffer; int /*<<< orphan*/  normalized; struct dir_baton* dir_baton; } ;
typedef  int /*<<< orphan*/  apr_ssize_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_UTF__UNKNOWN_LENGTH ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ ,char const*) ; 
 char const* normalized_collision ; 
 char const* normalized_unique ; 
 int /*<<< orphan*/  notify_warning (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 char* svn_hash_gets (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 void const* svn_relpath_join (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_repos_notify_warning_name_collision ; 
 int /*<<< orphan*/  svn_utf__normalize (char const**,void const*,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static svn_error_t *
check_name_collision(void *baton, const void *key, apr_ssize_t klen,
                     void *val, apr_pool_t *iterpool)
{
  struct check_name_collision_baton *const cb = baton;
  const char *name;
  const char *found;

  SVN_ERR(svn_utf__normalize(&name, key, klen, &cb->buffer));

  found = svn_hash_gets(cb->normalized, name);
  if (!found)
    svn_hash_sets(cb->normalized, apr_pstrdup(cb->buffer.pool, name),
                  normalized_unique);
  else if (found == normalized_collision)
    /* Skip already reported collision */;
  else
    {
      struct dir_baton *const db = cb->dir_baton;
      struct edit_baton *const eb = db->edit_baton;
      const char* normpath;

      svn_hash_sets(cb->normalized, apr_pstrdup(cb->buffer.pool, name),
                    normalized_collision);

      SVN_ERR(svn_utf__normalize(
                  &normpath, svn_relpath_join(db->path, name, iterpool),
                  SVN_UTF__UNKNOWN_LENGTH, &cb->buffer));
      notify_warning(iterpool, eb->notify_func, eb->notify_baton,
                     svn_repos_notify_warning_name_collision,
                     _("Duplicate representation of path '%s'"), normpath);
    }
  return SVN_NO_ERROR;
}