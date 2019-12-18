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
struct dir_baton_t {scalar_t__ users; int /*<<< orphan*/  pool; struct dir_baton_t* pb; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
maybe_done(struct dir_baton_t *db)
{
  db->users--;

  if (db->users == 0)
    {
      struct dir_baton_t *pb = db->pb;

      svn_pool_clear(db->pool);

      if (pb)
        SVN_ERR(maybe_done(pb));
    }

  return SVN_NO_ERROR;
}