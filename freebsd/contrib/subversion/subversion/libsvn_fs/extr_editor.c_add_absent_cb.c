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
typedef  int /*<<< orphan*/  svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_UNSUPPORTED_FEATURE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
add_absent_cb(void *baton,
              const char *relpath,
              svn_node_kind_t kind,
              svn_revnum_t replaces_rev,
              apr_pool_t *scratch_pool)
{
  /* This is a programming error. Code should not attempt to create these
     kinds of nodes within the FS.  */
  /* ### use a custom error code  */
  return svn_error_create(
           SVN_ERR_UNSUPPORTED_FEATURE, NULL,
           _("The filesystem does not support 'absent' nodes"));
}