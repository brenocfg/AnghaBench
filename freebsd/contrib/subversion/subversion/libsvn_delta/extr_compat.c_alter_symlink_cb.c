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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN__NOT_IMPLEMENTED () ; 

__attribute__((used)) static svn_error_t *
alter_symlink_cb(void *baton,
                 const char *relpath,
                 svn_revnum_t revision,
                 const char *target,
                 apr_hash_t *props,
                 apr_pool_t *scratch_pool)
{
  /* ### should we verify the kind is truly a symlink?  */

  /* ### do something  */

  SVN__NOT_IMPLEMENTED();
}