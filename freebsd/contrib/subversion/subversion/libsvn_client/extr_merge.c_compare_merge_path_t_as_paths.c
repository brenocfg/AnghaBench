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
struct TYPE_2__ {int /*<<< orphan*/  abspath; } ;
typedef  TYPE_1__ svn_client__merge_path_t ;

/* Variables and functions */
 int svn_path_compare_paths (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
compare_merge_path_t_as_paths(const void *a,
                              const void *b)
{
  const svn_client__merge_path_t *child1
    = *((const svn_client__merge_path_t * const *) a);
  const svn_client__merge_path_t *child2
    = *((const svn_client__merge_path_t * const *) b);

  return svn_path_compare_paths(child1->abspath, child2->abspath);
}