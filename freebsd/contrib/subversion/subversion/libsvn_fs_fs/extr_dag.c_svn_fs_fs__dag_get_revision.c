#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_fs_id_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_3__ {int /*<<< orphan*/ * id; int /*<<< orphan*/ * fresh_root_predecessor_id; } ;
typedef  TYPE_1__ dag_node_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_fs_fs__id_rev (int /*<<< orphan*/  const*) ; 

svn_error_t *
svn_fs_fs__dag_get_revision(svn_revnum_t *rev,
                            dag_node_t *node,
                            apr_pool_t *pool)
{
  /* In the special case that this is an unmodified transaction root,
     we need to actually get the revision of the noderev's predecessor
     (the revision root); see Issue #2608. */
  const svn_fs_id_t *correct_id = node->fresh_root_predecessor_id
    ? node->fresh_root_predecessor_id : node->id;

  /* Look up the committed revision from the Node-ID. */
  *rev = svn_fs_fs__id_rev(correct_id);

  return SVN_NO_ERROR;
}