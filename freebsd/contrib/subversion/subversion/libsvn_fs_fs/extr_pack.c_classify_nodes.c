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
typedef  int /*<<< orphan*/  svn_prefix_string__t ;
struct TYPE_3__ {void* is_head; int /*<<< orphan*/ * path; } ;
typedef  TYPE_1__ path_order_t ;

/* Variables and functions */
 void* TRUE ; 
 scalar_t__ svn_prefix_string__compare (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
classify_nodes(path_order_t **path_order,
               int count)
{
  const svn_prefix_string__t *path;
  int i;

  /* The logic below would fail for empty ranges. */
  if (count == 0)
    return;

  /* All entries are sorted by path, followed by revision.
   * So, the first index is also HEAD for the first path.
   */
  path = path_order[0]->path;
  path_order[0]->is_head = TRUE;

  /* Since the sorting implicitly groups all entries by path and then sorts
   * by descending revision within the group, whenever we encounter a new
   * path, the first entry is "HEAD" for that path.
   */
  for (i = 1; i < count; ++i)
    {
      /* New path? */
      if (svn_prefix_string__compare(path, path_order[i]->path))
        {
          path = path_order[i]->path;
          path_order[i]->is_head = TRUE;
        }
    }
}