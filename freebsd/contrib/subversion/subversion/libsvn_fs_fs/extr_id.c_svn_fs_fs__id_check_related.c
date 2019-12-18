#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_fs_id_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct TYPE_7__ {scalar_t__ revision; } ;
struct TYPE_5__ {TYPE_3__ node_id; TYPE_3__ txn_id; } ;
struct TYPE_6__ {TYPE_1__ private_id; } ;
typedef  TYPE_2__ fs_fs__id_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  svn_fs_fs__id_part_eq (TYPE_3__*,TYPE_3__*) ; 

svn_boolean_t
svn_fs_fs__id_check_related(const svn_fs_id_t *a,
                            const svn_fs_id_t *b)
{
  const fs_fs__id_t *id_a = (const fs_fs__id_t *)a;
  const fs_fs__id_t *id_b = (const fs_fs__id_t *)b;

  if (a == b)
    return TRUE;

  /* If both node_ids have been created within _different_ transactions
     (and are still uncommitted), then it is impossible for them to be
     related.

     Due to our txn-local temporary IDs, however, they might have been
     given the same temporary node ID.  We need to detect that case.
   */
  if (   id_a->private_id.node_id.revision == SVN_INVALID_REVNUM
      && id_b->private_id.node_id.revision == SVN_INVALID_REVNUM)
    {
      if (!svn_fs_fs__id_part_eq(&id_a->private_id.txn_id,
                                 &id_b->private_id.txn_id))
        return FALSE;

      /* At this point, matching node_ids implies relatedness. */
    }

  return svn_fs_fs__id_part_eq(&id_a->private_id.node_id,
                               &id_b->private_id.node_id);
}