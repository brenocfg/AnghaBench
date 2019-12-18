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
typedef  int /*<<< orphan*/  svn_error_t ;
struct dir_baton {int /*<<< orphan*/  pool; struct dir_baton* parent_baton; int /*<<< orphan*/  ref_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
maybe_release_dir_info(struct dir_baton *db)
{
  db->ref_count--;

  if (!db->ref_count)
    {
      struct dir_baton *pb = db->parent_baton;

      svn_pool_destroy(db->pool);

      if (pb)
        SVN_ERR(maybe_release_dir_info(pb));
    }

  return SVN_NO_ERROR;
}