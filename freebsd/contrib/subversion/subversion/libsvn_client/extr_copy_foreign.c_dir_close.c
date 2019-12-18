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
struct dir_baton_t {int dummy; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  ensure_added (struct dir_baton_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  maybe_done (struct dir_baton_t*) ; 

__attribute__((used)) static svn_error_t *
dir_close(void *dir_baton,
          apr_pool_t *scratch_pool)
{
  struct dir_baton_t *db = dir_baton;
  /*struct edit_baton_t *eb = db->eb;*/

  SVN_ERR(ensure_added(db, scratch_pool));

  SVN_ERR(maybe_done(db));

  return SVN_NO_ERROR;
}