#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  local_relpath; } ;
typedef  TYPE_1__ commit_queue_item_t ;

/* Variables and functions */
 int svn_path_compare_paths (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
compare_queue_items(const void *v1,
                    const void *v2)
{
  const commit_queue_item_t *cqi1
              = *(const commit_queue_item_t **)v1;
  const commit_queue_item_t *cqi2
              = *(const commit_queue_item_t **)v2;

  return svn_path_compare_paths(cqi1->local_relpath, cqi2->local_relpath);
}