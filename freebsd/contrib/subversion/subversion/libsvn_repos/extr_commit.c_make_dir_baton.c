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
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct edit_baton {int dummy; } ;
struct dir_baton {char const* path; int /*<<< orphan*/  base_rev; int /*<<< orphan*/  was_copied; int /*<<< orphan*/ * pool; struct dir_baton* parent; struct edit_baton* edit_baton; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 struct dir_baton* apr_pcalloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static struct dir_baton *
make_dir_baton(struct edit_baton *edit_baton,
               struct dir_baton *parent_baton,
               const char *full_path,
               svn_boolean_t was_copied,
               svn_revnum_t base_revision,
               apr_pool_t *pool)
{
  struct dir_baton *db;
  db = apr_pcalloc(pool, sizeof(*db));
  db->edit_baton = edit_baton;
  db->parent = parent_baton;
  db->pool = pool;
  db->path = full_path;
  db->was_copied = was_copied;
  db->base_rev = base_revision;
  return db;
}