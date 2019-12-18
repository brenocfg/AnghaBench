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
struct TYPE_2__ {int /*<<< orphan*/  url; } ;
typedef  TYPE_1__ svn_client_commit_item3_t ;

/* Variables and functions */
 int svn_path_compare_paths (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sort_commit_item_urls(const void *a, const void *b)
{
  const svn_client_commit_item3_t *item1
    = *((const svn_client_commit_item3_t * const *) a);
  const svn_client_commit_item3_t *item2
    = *((const svn_client_commit_item3_t * const *) b);
  return svn_path_compare_paths(item1->url, item2->url);
}