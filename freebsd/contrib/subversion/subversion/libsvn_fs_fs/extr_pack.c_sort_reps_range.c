#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_prefix_string__t ;
typedef  int /*<<< orphan*/  svn_fs_fs__id_part_t ;
typedef  int svn_boolean_t ;
struct TYPE_11__ {int /*<<< orphan*/  to; } ;
typedef  TYPE_2__ reference_t ;
struct TYPE_12__ {int predecessor_count; int /*<<< orphan*/  rep_id; int /*<<< orphan*/ * path; } ;
typedef  TYPE_3__ path_order_t ;
struct TYPE_13__ {int /*<<< orphan*/  references; TYPE_1__* fs; } ;
typedef  TYPE_4__ pack_context_t ;
struct TYPE_14__ {int max_linear_deltification; } ;
typedef  TYPE_5__ fs_fs_data_t ;
struct TYPE_10__ {TYPE_5__* fsap_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ compare_ref_to_item ; 
 int roundness (int) ; 
 scalar_t__ svn_fs_fs__id_part_eq (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_prefix_string__compare (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 TYPE_2__** svn_sort__array_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int (*) (void const*,void const*)) ; 

__attribute__((used)) static void
sort_reps_range(pack_context_t *context,
                path_order_t **path_order,
                path_order_t **temp,
                int first,
                int last)
{
  const svn_prefix_string__t *path;
  int i, dest;
  svn_fs_fs__id_part_t rep_id;
  fs_fs_data_t *ffd = context->fs->fsap_data;

  /* The logic below would fail for empty ranges. */
  if (first == last)
    return;

  /* Re-order noderevs like this:
   *
   * (1) Most likely to be referenced by future pack files, in path order.
   * (2) highest revision rep per path + dependency chain
   * (3) Remaining reps in path, rev order
   *
   * We simply pick & chose from the existing path, rev order.
   */
  dest = first;

  /* (1) There are two classes of representations that are likely to be
   * referenced from future shards.  These form a "hot zone" of mostly
   * relevant data, i.e. we try to include as many reps as possible that
   * are needed for future checkouts while trying to exclude as many as
   * possible that are likely not needed in future checkouts.
   *
   * First, "very round" representations from frequently changing nodes.
   * That excludes many in-between representations not accessed from HEAD.
   *
   * The second class are infrequently changing nodes.  Because they are
   * unlikely to change often in the future, they will remain relevant for
   * HEAD even over long spans of revisions.  They are most likely the only
   * thing we need from very old pack files.
   */
  for (i = first; i < last; ++i)
    {
      int round = roundness(path_order[i]->predecessor_count);

      /* Class 1:
       * Pretty round _and_ a significant stop in the node's delta chain.
       * This may pick up more than one representation from the same chain
       * but that's rare and not a problem.  Prefer simple checks here.
       *
       * The divider of 4 is arbitrary but seems to work well in practice.
       * Larger values increase the number of items in the "hot zone".
       * Smaller values make delta chains at HEAD more likely to contain
       * "cold zone" representations. */
      svn_boolean_t likely_target
        =    (round >= ffd->max_linear_deltification)
          && (round >= path_order[i]->predecessor_count / 4);

      /* Class 2:
       * Anything from short node chains.  The default of 16 is generous
       * but we'd rather include too many than too few nodes here to keep
       * seeks between different regions of this pack file at a minimum. */
      svn_boolean_t likely_head
        =   path_order[i]->predecessor_count
          < ffd->max_linear_deltification;

      /* Pick any node that from either class. */
      if (likely_target || likely_head)
        {
          temp[dest++] = path_order[i];
          path_order[i] = NULL;
        }
    }

  /* (2) For each (remaining) path, pick the nodes along the delta chain
   * for the highest revision.  Due to our ordering, this is the first
   * node we encounter for any path.
   *
   * Most references that don't hit a delta base picked in (1), will
   * access HEAD of the respective path.  Keeping all its dependency chain
   * in one place turns reconstruction into a linear scan of minimal length.
   */
  for (i = first; i < last; ++i)
    if (path_order[i])
      {
        /* This is the first path we still have to handle. */
        path = path_order[i]->path;
        rep_id = path_order[i]->rep_id;
        break;
      }

  for (i = first; i < last; ++i)
    if (path_order[i])
      {
        /* New path? */
        if (svn_prefix_string__compare(path, path_order[i]->path))
          {
            path = path_order[i]->path;
            rep_id = path_order[i]->rep_id;
          }

        /* Pick nodes along the deltification chain.  Skip side-branches. */
        if (svn_fs_fs__id_part_eq(&path_order[i]->rep_id, &rep_id))
          {
            reference_t **reference;

            temp[dest++] = path_order[i];
            path_order[i] = NULL;

            reference = svn_sort__array_lookup(context->references,
                                               &rep_id, NULL,
              (int (*)(const void *, const void *))compare_ref_to_item);
            if (reference)
              rep_id = (*reference)->to;
          }
      }

  /* (3) All remaining nodes in path, rev order.  Linear deltification
   * makes HEAD delta chains from (2) cover all or most of their deltas
   * in a given pack file.  So, this is just a few remnants that we put
   * at the end of the pack file.
   */
  for (i = first; i < last; ++i)
    if (path_order[i])
      temp[dest++] = path_order[i];

  /* We now know the final ordering. */
  assert(dest == last);
}