#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  trail_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int svn_boolean_t ;
struct TYPE_6__ {int /*<<< orphan*/  data_key_uniquifier; int /*<<< orphan*/  data_key; int /*<<< orphan*/  prop_key; } ;
typedef  TYPE_1__ node_revision_t ;
struct TYPE_7__ {int /*<<< orphan*/  id; int /*<<< orphan*/  fs; } ;
typedef  TYPE_2__ dag_node_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ svn_fs_base__same_keys (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_bdb__get_node_revision (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_base__things_different(svn_boolean_t *props_changed,
                              svn_boolean_t *contents_changed,
                              dag_node_t *node1,
                              dag_node_t *node2,
                              trail_t *trail,
                              apr_pool_t *pool)
{
  node_revision_t *noderev1, *noderev2;

  /* If we have no place to store our results, don't bother doing
     anything. */
  if (! props_changed && ! contents_changed)
    return SVN_NO_ERROR;

  /* The node revision skels for these two nodes. */
  SVN_ERR(svn_fs_bdb__get_node_revision(&noderev1, node1->fs, node1->id,
                                        trail, pool));
  SVN_ERR(svn_fs_bdb__get_node_revision(&noderev2, node2->fs, node2->id,
                                        trail, pool));

  /* Compare property keys. */
  if (props_changed != NULL)
    *props_changed = (! svn_fs_base__same_keys(noderev1->prop_key,
                                               noderev2->prop_key));

  /* Compare contents keys and their (optional) uniquifiers. */
  if (contents_changed != NULL)
    *contents_changed =
      (! (svn_fs_base__same_keys(noderev1->data_key,
                                 noderev2->data_key)
          /* Technically, these uniquifiers aren't used and "keys",
             but keys are base-36 stringified numbers, so we'll take
             this liberty. */
          && (svn_fs_base__same_keys(noderev1->data_key_uniquifier,
                                     noderev2->data_key_uniquifier))));

  return SVN_NO_ERROR;
}