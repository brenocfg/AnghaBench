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
typedef  int /*<<< orphan*/  svn_revnum_t ;
struct edit_baton {int /*<<< orphan*/  path; } ;
struct dir_baton {char const* path; char const* cmp_path; int /*<<< orphan*/ * pool; void* check_name_collision; int /*<<< orphan*/  deleted_entries; void* written_out; int /*<<< orphan*/  cmp_rev; struct edit_baton* edit_baton; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT_NO_RETURN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_hash_make (int /*<<< orphan*/ *) ; 
 struct dir_baton* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 char* apr_pstrdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* svn_relpath_canonicalize (char const*,int /*<<< orphan*/ *) ; 
 char* svn_relpath_join (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct dir_baton *
make_dir_baton(const char *path,
               const char *cmp_path,
               svn_revnum_t cmp_rev,
               void *edit_baton,
               struct dir_baton *pb,
               apr_pool_t *pool)
{
  struct edit_baton *eb = edit_baton;
  struct dir_baton *new_db = apr_pcalloc(pool, sizeof(*new_db));
  const char *full_path;

  /* A path relative to nothing?  I don't think so. */
  SVN_ERR_ASSERT_NO_RETURN(!path || pb);

  /* Construct the full path of this node. */
  if (pb)
    full_path = svn_relpath_join(eb->path, path, pool);
  else
    full_path = apr_pstrdup(pool, eb->path);

  /* Remove leading slashes from copyfrom paths. */
  if (cmp_path)
    cmp_path = svn_relpath_canonicalize(cmp_path, pool);

  new_db->edit_baton = eb;
  new_db->path = full_path;
  new_db->cmp_path = cmp_path;
  new_db->cmp_rev = cmp_rev;
  new_db->written_out = FALSE;
  new_db->deleted_entries = apr_hash_make(pool);
  new_db->check_name_collision = FALSE;
  new_db->pool = pool;

  return new_db;
}