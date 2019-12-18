#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char const* abspath; } ;
typedef  TYPE_1__ svn_client__merge_path_t ;
struct TYPE_8__ {int /*<<< orphan*/  elt_size; int /*<<< orphan*/  nelts; int /*<<< orphan*/  elts; } ;
typedef  TYPE_2__ apr_array_header_t ;

/* Variables and functions */
 TYPE_1__** bsearch (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compare_merge_path_t_as_paths ; 

__attribute__((used)) static svn_client__merge_path_t *
get_child_with_mergeinfo(const apr_array_header_t *children_with_mergeinfo,
                         const char *abspath)
{
  svn_client__merge_path_t merge_path;
  svn_client__merge_path_t *key;
  svn_client__merge_path_t **pchild;

  merge_path.abspath = abspath;
  key = &merge_path;
  pchild = bsearch(&key, children_with_mergeinfo->elts,
                   children_with_mergeinfo->nelts,
                   children_with_mergeinfo->elt_size,
                   compare_merge_path_t_as_paths);
  return pchild ? *pchild : NULL;
}